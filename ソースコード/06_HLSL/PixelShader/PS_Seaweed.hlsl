//- 海藻の揺れが合わさったディザ抜き
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 normal : NORMAL0;
    float4 worldPos : POSITION0;
    float4 viewPos : POSITION1;
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

Texture2D tex : register(t0);
Texture2D Dizatex : register(t1);
SamplerState samp : register(s0);


float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    //- ゆらゆら揺れるアニメーションを行う
    float2 noiseUV = pin.uv;
    noiseUV.x += sin(noiseUV.y + Time.time);       //時間経過でUV座標を変更
    color = tex.Sample(samp, noiseUV) * pin.color; //ディザ抜きの為に色を取得
    
    //- 距離に応じてアルファ値を変化させる
    float len = length(pin.worldPos.xyz - Object.oPos.xyz);
    float distScale = 0.05f;
    len *= distScale; //距離を調整する
    color.a *= saturate(len);//0～1にクランプ
    
    //- ディザ抜き
    float ditherScale = 10.0f;  //ディザの大きさ
    /*
    シェーダーを適応したものが、一定の角度になるとディザが正しく適応されないので、
    ビュー座標に応じてディザパターンを適応
    */
    float2 ditherUV = (pin.viewPos.xy / pin.viewPos.w);
    ditherUV *= ditherScale; //ディザの大きさを調整
    float dither = Dizatex.Sample(samp, ditherUV).r;
    //- アルファ値がディザより小さい場合はピクセルを破棄する
    if (color.a < dither){ discard; }
    
    return color;
}