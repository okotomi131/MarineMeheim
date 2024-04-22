//- リロード時間に応じてゲージの表示を変化させる
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
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
SamplerState samp : register(s0);


float4 main(PS_IN pin) : SV_TARGET
{
    float4 Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    //- 現在のゲージの大きさがUV座標より大きい場合は破棄
    if (pin.uv.y < 1.0f - Object.oScale.y) { discard; }
    
    Color  = tex.Sample(samp, pin.uv);
    //赤色からスタートさせる
    Color *= float4(1.0f, Object.oScale.y, Object.oScale.y, 1.0f);
    
    return Color;
}