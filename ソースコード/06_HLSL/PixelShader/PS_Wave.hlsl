//- �Z�����[�m�C�Y���g�p���A�R�[�X�e�B�N�X�\�����s��

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float4 worldPos : POSITION0;
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

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


/*
�Q�l��
https://meganeunity.hateblo.jp/entry/2019/05/15/074607

�Z�����[�m�C�Y
https://thebookofshaders.com/12/?lan=jp
����_����ł��߂��Z�����̓_�܂ł̋������g�p���ăm�C�Y�𐶐�����
*/

static const float2 RandomNum = float2(127.1f, 311.7f); //
static const float2 RandomNum2 = float2(269.5f, 183.3f);
static const float RandomScale = 43758.5453f;
static const float Pi2 = 6.2831f;

/**
* @brief 2�����̃����_���x�N�g�����쐬����
* @param p �����_���x�N�g�����쐬���邽�߂̃x�N�g��
* @return �쐬���������_���x�N�g��
*/
float2 Random2(float2 p)
{
    //- ���ς̌v�Z���g�p���Ap�ɑ΂��ďd�ݕt�����s��
    float dot1 = dot(p, RandomNum); 
    float dot2 = dot(p, RandomNum2);
    //- sin���g�p���āA-1�`1�͈̔͂ɂ���
    float2 sinNum = sin(float2(dot1, dot2));
    //- -1�`1�͈̔͂��X�P�[�����̕��Ɋg�傷��
    //andomScale = 10�Ȃ�΁A-10�`10�͈̔͂ɂȂ�
    float2 scale = sinNum * RandomScale;
    //- frac���g�p���āA�����_�ȉ����擾
    float2 fracNum = frac(scale);
    return fracNum;   
}

/**
 * @brief �Z�����[�m�C�Y���쐬����
 * @param _uv �e�N�X�`�����W
 * @param scale ���삷��}�X�̐�
 * @return ���삵���Z�����[�m�C�Y
 */
float CellularNoise(float2 _uv, float scale)
{

    //- �}�X�ڂɕ������s��
    /*
    floor�F���������̒l��ԋp
    frac�F���������̒l��ԋp
    
    �EfUV��iUV
    uv���W��0�`1�ł��邪�A_uv��scale�{��0�`scale�͈͂�XY���ʂɂ���
    ���̌�A���������Ə��������ɕ������
    fUV�͏����_�ȉ���0�`9(�}�X�ڂ𕪊�����
    iUV�͐���������0�`scale(�}�X�ڂ̒l������
    �̒l�͈̔͂ɂȂ�
    */
    _uv *= scale;           //�e�N�X�`�����W���X�P�[��
    int iUV = floor(_uv);   //���������F 0�`scale
    float2 fUV = frac(_uv); //���������F.0�`.9
    float minDist = 2.0f; //�ŒZ����

    
    /*
    ���݂̃Z���𒆐S�Ƃ��A����3x3�̃Z���𒲂ׂ�
    ������ ���F(0,0)�@��_
    ������ ���F��_�̎��͂̃Z��
    ������
    */

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            float2 cell = float2(x, y);//xy�����ɂ���}�X���W���ߗ׃}�X�Ƃ��ēo�^
            float addUnderLeftPos = 0.5f;//�}�X�̍���������Z������W
            float range = 0.5f;//�}�X�̒��ɓ_�����܂�悤�ɁA�͈͂�ݒ肷��
            float2 movePoint = float2(0.0f, 0.0f);//�ړ�����_
            
            /*
            �����������ɕʁX�̃s�N�Z���ł����Ă������}�X�ł���Έ�̓_�����
            iUV�͌��ݕ`�悵�Ă���s�N�Z��������}�X�̐�΍��W������
            cell�̓��[�v���Ō��ݒ��ׂĂ���}�X�̑��΍��W������
            
            ���̓�𑫂����킹�邱�ƂŁA
            ���ݒ��ׂĂ���}�X�̐�΍��W���擾�ł���B
            ���ׁ̈A���̃}�X�Ɨ�������邱�Ƃ�h����
            */
            float2 rondomNum = Random2(iUV + cell);
            
            /*
            ���Ԍo�߂ňړ�������ׁAsin�֐����g�p
            Pi2(6.2831)�F�����_���ړ��̋K������ύX�ł���H
            ���v�����̕K�v�L�A����͂��̂܂܎g�p
            */
            float2 timeMove = sin(Time.time + Pi2 * rondomNum);
            
            //- �}�X�̒��ɓ_�����܂�悤�ɁA�͈͂�ݒ肷��
            float createPoint = 0.5 + 0.5 * timeMove;
            
            //- ���݂̃s�N�Z���Ɠ����_�Ƃ̍��x�N�g�����v�Z
            float2 diff = cell + createPoint - fUV;
            float dist = length(diff); //�x�N�g���̒������v�Z
            //- �ŏ��������X�V����
            minDist = min(minDist, dist);
        }
    }
    //- �l�𔼕��ɂ��Ē���
    return minDist * 0.5f;
}

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = g_Texture.Sample(g_SamplerState, pin.uv);
    color *= pin.color;

    // �Z�����[�m�C�Y��ǉ�
    float noise = CellularNoise(pin.uv, 2.0f);
    //- �F�̐������������Ē�������
    color.rgb *= noise * float3(2.5f, 2.5f, -0.5f) + float3(0.8f, 0.8f, 1.2f);

    return color;
}

