//- �C���̗h�ꂪ���킳�����f�B�U����
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 normal : NORMAL0;
    float4 worldPos : POSITION0;
    float4 viewPos : POSITION1;
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
    //- �����h���A�j���[�V�������s��
    float2 noiseUV = pin.uv;
    noiseUV.x += sin(noiseUV.y + Time.time);       //���Ԍo�߂�UV���W��ύX
    color = tex.Sample(samp, noiseUV) * pin.color; //�f�B�U�����ׂ̈ɐF���擾
    
    //- �����ɉ����ăA���t�@�l��ω�������
    float len = length(pin.worldPos.xyz - Object.oPos.xyz);
    float distScale = 0.05f;
    len *= distScale; //�����𒲐�����
    color.a *= saturate(len);//0�`1�ɃN�����v
    
    //- �f�B�U����
    float ditherScale = 10.0f;  //�f�B�U�̑傫��
    /*
    �V�F�[�_�[��K���������̂��A���̊p�x�ɂȂ�ƃf�B�U���������K������Ȃ��̂ŁA
    �r���[���W�ɉ����ăf�B�U�p�^�[����K��
    */
    float2 ditherUV = (pin.viewPos.xy / pin.viewPos.w);
    ditherUV *= ditherScale; //�f�B�U�̑傫���𒲐�
    float dither = Dizatex.Sample(samp, ditherUV).r;
    //- �A���t�@�l���f�B�U��菬�����ꍇ�̓s�N�Z����j������
    if (color.a < dither){ discard; }
    
    return color;
}