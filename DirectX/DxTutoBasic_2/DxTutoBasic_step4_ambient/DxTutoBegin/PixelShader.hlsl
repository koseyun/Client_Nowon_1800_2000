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
	float4 ambientColor;
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // 법선데이터
	float2 Tex:TEXCOORD0;
	
	//float4 Color:COLOR0;
};

//float4 main():SV_TARGET
//float4 main(VS_OUTPUT i):SV_TARGET
float4 main(PS_INPUT i) :SV_TARGET
{
	// 최종 색상
	float4 color = 0;

	// 주변광
	// 기본 색상을 주변광으로 일단 설정
	color = ambientColor;

	// 난반사광
	// 난반사 색상
	float4 diffuseColor = 0;
	// 광량(빛의 세기)
	float lightIntensity = 0;
	lightIntensity = saturate(dot(LightDir, i.Norm)); // 램버트 조명모델

	// 광량(난반사 결과로 나온 광량)이 0보다 큰 경우에만 색상곱셈연산 수행
	// (왜냐하면 0인 경우를 하면 오히려 색상이 사라진다 -->0)
	if (lightIntensity > 0.0f)
	{
		diffuseColor = LightColor * lightIntensity; // 난반사 색상 구함

		color = color + diffuseColor;
	}

	// 텍스쳐 색상
	float4 texColor = txDiffuse.Sample(samLinear, i.Tex);	

	// 텍스쳐 색상과 조명(주변광, 난반사광)색상을 결합			// 중요!!
	//color = texColor * diffuseColor;
	color = texColor * color;
	color.a = 1;

	return color;
}