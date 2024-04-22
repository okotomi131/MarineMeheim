//- 近づくと現れるディザ抜きの逆を行う
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 normal : NORMAL0;
    float4 worldPos : POSITION0;
    float4 screenPos : POSITION1;
    float4 viewPos : POSITION2;
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

    //- ゆれるアニメーションを行う
    float2 noiseUV = pin.uv;
    noiseUV.x += sin(noiseUV.y + Time.time);
    noiseUV.y += cos(noiseUV.x + Time.time);
    color = tex.Sample(samp, noiseUV);
    color *= pin.color;;

    //- 距離に応じてアルファ値を変化させる
    float len = length(pin.worldPos.xyz - Object.oPos.xyz);
    float distScale = 0.015f;
    len *= distScale; //距離を調整する
    color.a *= saturate(len); //0～1にクランプ
    
    //- ディザ抜き
    float ditherScale = 12.0f; //ディザの大きさ
    /*
    シェーダーを適応したものが、一定の角度になるとディザが正しく適応されないので、
    ビュー座標に応じてディザパターンを適応
    */
    float2 ditherUV = (pin.viewPos.xy / pin.viewPos.w);
    ditherUV = ditherUV * 0.5f;//-1.0f～1.0fの範囲に収める
    ditherUV = ditherUV + 0.5f;// 0.0f～1.0fの範囲に収める
    ditherUV *= ditherScale;
    
    float dither = Dizatex.Sample(samp, ditherUV).r;
    if (color.a > dither) { discard; }
    
    return color;

}