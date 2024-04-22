//- ライトの情報をテクスチャに適応する
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 worldPos : POSITION0;
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


float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    color = g_Texture.Sample(g_SamplerState, pin.uv);
    color *= pin.color;
    
    return color;
}