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

	float4 ambientColor; // 주변광

	// 정반사
	float3 cameraPosition;	// 카메라의 위치
	float specularPower;	// 정반사 강도(날카로움)
	float4 specularColor;	// 정반사광 색상
};

struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // 법선데이터
	float2 Tex:TEXCOORD0;	
	// 시선벡터
	float3 viewDir:TEXCOORD1;
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

	// 정반사광
	float3 reflectDir = 0; // 반사벡터
	float4 specular = 0; // 최종적으로 구해지는 정반사 색상

	// 광량(난반사 결과로 나온 광량)이 0보다 큰 경우에만 색상곱셈연산 수행
	// (왜냐하면 0인 경우를 하면 오히려 색상이 사라진다 -->0)
	if (lightIntensity > 0.0f)
	{
		diffuseColor = LightColor * lightIntensity; // 난반사 색상 구함
		// 색상 더하기 연산으로 색상값이 더 밝아지게
		color = color + diffuseColor;

		// 정반사 벡터를 구한다
		//reflectDir = normalize(LightDir + 2.0f * dot(-1.0f * LightDir, i.Norm) * i.Norm);
		reflectDir = reflect(LightDir, i.Norm); // 셰이더 함수, 반사
		specular = pow(saturate(dot(-1.0f * reflectDir, i.viewDir)), specularPower); // 거듭제곱 pow
		// float4 <-- float
	}

	// 텍스쳐 색상
	float4 texColor = txDiffuse.Sample(samLinear, i.Tex);	

	// 텍스쳐 색상과 조명(주변광, 난반사광)색상을 결합			// 중요!!
	//color = texColor * diffuseColor;
	color = texColor * color;
	// 정반사광도 적용 : 색상의 덧셈 연산이라는 것에 주의, 더 밝게 하는 것이다
	color = saturate(color + specular);
	color.a = 1;

	return color;
}