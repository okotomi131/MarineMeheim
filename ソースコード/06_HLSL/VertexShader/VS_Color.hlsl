cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix proj;
}

struct MATERIAL
{
    float4 ambient;
    float4 color;
    float4 specular;
    float4 emission;
    float shininess;
    bool textureEnable;
    float2 dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

struct VS_IN
{
    float4 pos : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    matrix wvp;
    wvp = mul(world, view);
    wvp = mul(wvp, proj);
    
    vout.pos = mul(vin.pos, wvp);
    vout.uv = vin.uv;
    vout.color = vin.color * Material.color;
    
    return vout;
}