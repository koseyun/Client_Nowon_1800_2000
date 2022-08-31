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

struct VS_INPUT
{
	float4 Pos:POSITION; // <--주의 : 여기는 4로 맞춰야 한다. 3이면 작동 안함
	float3 Norm:NORMAL; // 법선데이터
	float2 Tex:TEXCOORD0;
};

//struct VS_OUTPUT
struct PS_INPUT
{
	float4 Pos:SV_POSITION;
	float3 Norm:NORMAL; // 법선데이터
	float2 Tex:TEXCOORD0;
	
	//float4 Color:COLOR0;
};

// 매개변수로 들어오는 것은 IA에서 전달받은 것이다
// 리턴 값은 Pixel Shader로 전달된다

// 정점 셰이더 : 정점 하나당 작동하는 프로그램
//float4 main( float4 pos : POSITION, float4 Color:COLOR ) : SV_POSITION // SystemValue 시맨틱
//VS_OUTPUT main(float4 pos : POSITION, float4 Color : COLOR)
PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;
	
	// 이 물체의 월드 상에서의 위치
	// 시선벡터를 구하기 위한 한 요소로 이 물체의 위치 데이터가 필요
	float4 worldPosition;

	// IA에서 넘겨받은 정점 위치데이터에
	// 월드, 뷰, 투영 변환을 적용한다
	o.Pos = mul(i.Pos, World);		// mul 셰이더 함수, 벡터와 행렬의 곱셈

	// 월드 상에서의 정점의 위치를 적재시켜놓는다
	worldPosition = o.Pos;

	o.Pos = mul(o.Pos, View);
	o.Pos = mul(o.Pos, Projection);
	
	o.Norm = mul(float4(i.Norm, 0), World).xyz;
	o.Tex = i.Tex;

	return o;
}