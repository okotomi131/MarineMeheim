//- ドットにする
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

// テクスチャを受け取る
Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{

    float dotSize = 0.15f; //ドットサイズ
    float2 dotUV = floor(pin.uv / dotSize) * dotSize;
    // テクスチャからドットの色を取得
    float4 dotColor = tex.Sample(samp, dotUV);

    // ドットの色と頂点からの色を乗算
    dotColor *= pin.color;

    return dotColor;
}