
/*struct VS_OUTPUT
{
	float4 Pos:SV_POSITION;
	float4 Color:COLOR0;
};*/

//Texture2D txDiffuse;
//SamplerState samLinear;

// 슬롯 번호를 명시적으로 지정해 줄 수 있다
// 지정하지 않으면 자동으로 매겨준다
Texture2D txDiffuse:register(t0); // texture 0번 슬롯
SamplerState samLinear:register(s0); //sampler 0번 슬롯

// cbuffer 상수버퍼 만들기 예약어
// 16byte 단위로 정렬해야 안전
cbuffer CBTransform:register(b0) //<-- buffer 0번 슬롯
{
	matrix World;		// 전역변수 : 이 파일 전체에서 유효한 변수		4 * 4*4 = 64byte
	matrix View;		// 전역변수 : 이 파일 전체에서 유효한 변수
	matrix Projection;	// 전역변수 : 이 파일 전체에서 유효한 변수

	float4 LightDir;
	float4 LightColor;
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // 법선데이터
	float2 Tex:TEXCOORD0;
	
	//float4 Color:COLOR0;
};

// Vertex Shader로부터 데이터를 전달받는다
// 최종적으로는 최종 픽셀색상값을 만들어낸다

//float4 main() : SV_TARGET
//float4 main(VS_OUTPUT i) :SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);

	// 이제 vertex shading단계에서 전달받은 정점의 색상으로 픽셀을 칠한다
	//return i.Color;

	// 셰이더 코드에서 색상연산은 자릿수가 같은 것끼리만 가능하다
	// 단, 한자릿수는 모든 자릿수와 연산이 가능하다
	//float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);//0;
	
	float4 color = 0;

	// 빛 벡터와 법선벡터를 이용하여 음영을 만들자		
	// 셰이더에서 제공하는 함수
	
	// float3 light = (0.0f, 0.0f, -1.0f);
	
	// 광량 = 빛벡터 dot 법선벡터 <--[-1,1]
	// 범위제한(광향) <-- [0,1]
	// 최종색상 = 광량 * 조명색상 <-- 광량은 float, 조명색상은 float4
	color = saturate(dot(LightDir, i.Norm)) * LightColor;
	color.a = 1;

	// 텍스쳐를 참고하여 픽셀의 색상을 결정한다. UV좌표를 기반으로 샘플링한다
	// 샘플링한 텍스쳐(의 색상정보)와 위에서 계산한 조명(적용 색상정보)를 색상연산 곱셈하여 최종색상 결정
	color = txDiffuse.Sample(samLinear, i.Tex) * color;

	return color;
}