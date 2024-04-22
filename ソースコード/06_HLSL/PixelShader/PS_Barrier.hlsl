//- �߂Â��ƌ����f�B�U�����̋t���s��
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

    //- ����A�j���[�V�������s��
    float2 noiseUV = pin.uv;
    noiseUV.x += sin(noiseUV.y + Time.time);
    noiseUV.y += cos(noiseUV.x + Time.time);
    color = tex.Sample(samp, noiseUV);
    color *= pin.color;;

    //- �����ɉ����ăA���t�@�l��ω�������
    float len = length(pin.worldPos.xyz - Object.oPos.xyz);
    float distScale = 0.015f;
    len *= distScale; //�����𒲐�����
    color.a *= saturate(len); //0�`1�ɃN�����v
    
    //- �f�B�U����
    float ditherScale = 12.0f; //�f�B�U�̑傫��
    /*
    �V�F�[�_�[��K���������̂��A���̊p�x�ɂȂ�ƃf�B�U���������K������Ȃ��̂ŁA
    �r���[���W�ɉ����ăf�B�U�p�^�[����K��
    */
    float2 ditherUV = (pin.viewPos.xy / pin.viewPos.w);
    ditherUV = ditherUV * 0.5f;//-1.0f�`1.0f�͈̔͂Ɏ��߂�
    ditherUV = ditherUV + 0.5f;// 0.0f�`1.0f�͈̔͂Ɏ��߂�
    ditherUV *= ditherScale;
    
    float dither = Dizatex.Sample(samp, ditherUV).r;
    if (color.a > dither) { discard; }
    
    return color;

}