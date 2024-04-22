//- セルラーノイズを使用し、コースティクス表現を行う

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 worldPos : POSITION0;
};

struct TIME
{
    float time;
    float3 dummy;
};

cbuffer TimeBuffer : register(b5)
{
    TIME Time;
};

struct OBJECT
{
    float3 oPos;
    float3 oScale;
    float2 dummy;
};

cbuffer ObjectBuffer : register(b6)
{
    OBJECT Object;
};

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


/*
参考先
https://meganeunity.hateblo.jp/entry/2019/05/15/074607

セルラーノイズ
https://thebookofshaders.com/12/?lan=jp
ある点から最も近いセル内の点までの距離を使用してノイズを生成する
*/

static const float2 RandomNum = float2(127.1f, 311.7f); //
static const float2 RandomNum2 = float2(269.5f, 183.3f);
static const float RandomScale = 43758.5453f;
static const float Pi2 = 6.2831f;

/**
* @brief 2次元のランダムベクトルを作成する
* @param p ランダムベクトルを作成するためのベクトル
* @return 作成したランダムベクトル
*/
float2 Random2(float2 p)
{
    //- 内積の計算を使用し、pに対して重み付けを行う
    float dot1 = dot(p, RandomNum); 
    float dot2 = dot(p, RandomNum2);
    //- sinを使用して、-1～1の範囲にする
    float2 sinNum = sin(float2(dot1, dot2));
    //- -1～1の範囲をスケール分の幅に拡大する
    //andomScale = 10ならば、-10～10の範囲になる
    float2 scale = sinNum * RandomScale;
    //- fracを使用して、小数点以下を取得
    float2 fracNum = frac(scale);
    return fracNum;   
}

/**
 * @brief セルラーノイズを作成する
 * @param _uv テクスチャ座標
 * @param scale 制作するマスの数
 * @return 制作したセルラーノイズ
 */
float CellularNoise(float2 _uv, float scale)
{

    //- マス目に分割を行う
    /*
    floor：整数部分の値を返却
    frac：小数部分の値を返却
    
    ・fUVとiUV
    uv座標は0～1であるが、_uvをscale倍し0～scale範囲のXY平面にする
    その後、整数部分と小数部分に分けると
    fUVは小数点以下の0～9(マス目を分割する
    iUVは整数部分の0～scale(マス目の値を示す
    の値の範囲になる
    */
    _uv *= scale;           //テクスチャ座標をスケール
    int iUV = floor(_uv);   //整数部分： 0～scale
    float2 fUV = frac(_uv); //小数部分：.0～.9
    float minDist = 2.0f; //最短距離

    
    /*
    現在のセルを中心とし、周囲3x3のセルを調べる
    □□□ ■：(0,0)　基点
    □■□ □：基点の周囲のセル
    □□□
    */

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            float2 cell = float2(x, y);//xy方向にあるマス座標を近隣マスとして登録
            float addUnderLeftPos = 0.5f;//マスの左下から加算する座標
            float range = 0.5f;//マスの中に点が留まるように、範囲を設定する
            float2 movePoint = float2(0.0f, 0.0f);//移動する点
            
            /*
            乱数生成時に別々のピクセルであっても同じマスであれば一つの点を取る
            iUVは現在描画しているピクセルがいるマスの絶対座標がいる
            cellはループ内で現在調べているマスの相対座標がいる
            
            この二つを足し合わせることで、
            現在調べているマスの絶対座標を取得できる。
            その為、他のマスと乱数が被ることを防げる
            */
            float2 rondomNum = Random2(iUV + cell);
            
            /*
            時間経過で移動させる為、sin関数を使用
            Pi2(6.2831)：ランダム移動の規則性を変更できる？
            ↑要調査の必要有、今回はそのまま使用
            */
            float2 timeMove = sin(Time.time + Pi2 * rondomNum);
            
            //- マスの中に点が留まるように、範囲を設定する
            float createPoint = 0.5 + 0.5 * timeMove;
            
            //- 現在のピクセルと動く点との差ベクトルを計算
            float2 diff = cell + createPoint - fUV;
            float dist = length(diff); //ベクトルの長さを計算
            //- 最小距離を更新する
            minDist = min(minDist, dist);
        }
    }
    //- 値を半分にして調整
    return minDist * 0.5f;
}

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = g_Texture.Sample(g_SamplerState, pin.uv);
    color *= pin.color;

    // セルラーノイズを追加
    float noise = CellularNoise(pin.uv, 2.0f);
    //- 色の成分を強調して調整する
    color.rgb *= noise * float3(2.5f, 2.5f, -0.5f) + float3(0.8f, 0.8f, 1.2f);

    return color;
}

