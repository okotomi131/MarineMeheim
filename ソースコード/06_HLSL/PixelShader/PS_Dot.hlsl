//- �h�b�g�ɂ���
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

// �e�N�X�`�����󂯎��
Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{

    float dotSize = 0.15f; //�h�b�g�T�C�Y
    float2 dotUV = floor(pin.uv / dotSize) * dotSize;
    // �e�N�X�`������h�b�g�̐F���擾
    float4 dotColor = tex.Sample(samp, dotUV);

    // �h�b�g�̐F�ƒ��_����̐F����Z
    dotColor *= pin.color;

    return dotColor;
}