
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
    float4 normal : NORMAL0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 normal : NORMAL0;
    float4 worldPos : POSITION0;
    float4 screenPos : POSITION1;
};


VS_OUT main(VS_IN vin)
{
    VS_OUT vout;
    
    vout.pos = mul(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    
    vout.worldPos = vout.pos;
    vout.screenPos = vout.pos;
    
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);
    
     //- ���[���h���W�ɕϊ�
    float4 wNormal, Normal;
    Normal = float4(vin.normal.xyz, 0.0);
    wNormal = mul(Normal, world);
    wNormal = normalize(wNormal);
    vout.normal = wNormal;

    //- �F�̌v�Z
    vout.color = vin.color * Material.color; //�g�U��
    vout.color += vin.color * Material.ambient; //����
    vout.color += Material.emission; //���Ȕ���
    vout.color.a = vin.color.a * Material.color.a; //�A���t�@�l
    
    vout.uv = vin.uv;
    return vout;
}