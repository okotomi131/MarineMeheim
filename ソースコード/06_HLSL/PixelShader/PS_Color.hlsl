struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

// テクスチャを受け取る
Texture2D tex : register(t0);
SamplerState samp : register(s0); // テクスチャの繰り返し設定

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f,0.0f,0.0f, 0.0f);
    color = pin.color;
    
    return color;
}