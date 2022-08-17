// 매개변수로 들어오는 것은 IA에서 전달받은 것이다
// 리턴 값은 Pixel Shader로 전달된다

// 정점 셰이더 : 정점 하나당 작동하는 프로그램
float4 main( float4 pos : POSITION ) : SV_POSITION // SEMANTIC 시맨틱
{
	return pos;
}