//- �����[�h���Ԃɉ����ăQ�[�W�̕\����ω�������
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
    
    //- ���݂̃Q�[�W�̑傫����UV���W���傫���ꍇ�͔j��
    if (pin.uv.y < 1.0f - Object.oScale.y) { discard; }
    
    Color  = tex.Sample(samp, pin.uv);
    //�ԐF����X�^�[�g������
    Color *= float4(1.0f, Object.oScale.y, Object.oScale.y, 1.0f);
    
    return Color;
}