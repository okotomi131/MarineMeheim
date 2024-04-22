
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
    float  shininess;
    bool   textureEnable;
    float2 dummy;
};

cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

struct LIGHT
{
    bool   Enable;
    bool3  Dummy;
    float4 Direction;
    float4 Color;
    float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
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
    float4 worldPos : POSITION0;
};

VS_OUT main( VS_IN vin)
{
    VS_OUT vout;
    
    //- �s��̌���
    vout.pos = mul(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    
    vout.worldPos = vout.pos;
    
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);
    
    //- ���[���h���W�ɕϊ�
    float4 wNormal, Normal;
    Normal = float4(vin.normal.xyz, 0.0);
    wNormal = mul(Normal, world);
    wNormal = normalize(wNormal);
    
    //- ���̕���
    float light = -dot(Light.Direction.xyz, wNormal.xyz);//���ς��g�p���Ċg�U�����v�Z
    light = saturate(light);//0�`1�͈̔͂Ɏ��߂�

    //- �F�̌v�Z
    vout.color = vin.color * Material.color * light * Light.Color; //�g�U��
    vout.color += vin.color * Material.ambient * Light.Ambient;      //����
    vout.color += Material.emission;                 //���Ȕ���
    vout.color.a = vin.color.a * Material.color.a; //�A���t�@�l
   
    vout.uv = vin.uv;
    
    return vout;
}