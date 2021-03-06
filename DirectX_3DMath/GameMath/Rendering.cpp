/*
	렌더링(Rendering) : 3D 월드에 있는 정점 단위의 물체들을 최종적으로 2D 모니터의 픽셀 단위의 프레임으로 만드는 것

	렌더링 파이프라인 : 렌더링의 단계별 공정들의 집합

		다음은 일반적인 공정 분류이다

		----------------------------------------------------------------------------------------------------
		응용단계                          기하(geometry)단계                          래스터라이즈 단계
		----------------------------------------------------------------------------------------------------
		                 월드변환     뷰변환        투영변환	     뷰포트변환
							                        (3D->2D)	     임의의 스크린 영역에 2D표시


		----------------------------------------------------------------------------------------------------
		CPU, RAM                            GPU, VRAM                                  GPU, VRAM


		                 정점단위로 데이터를 다룬다                                    픽셀단위로 데이터를 다룬다
						 연속적인 공간                                                 불연속적인 공간이다
						 vertex shader가 위치한다                                      pixel shader가 위치한다


	shader : 셰이딩(최종 색상 결정)을 수행하는 작은 조각프로그램
	- vertex shader : 정점단위로 셰이딩 프로그램을 수행한다
	- pixel shader : 픽셀단위로 셰이딩 프로그램을 수행한다

	변환(Transform) : 자기자신으로의 사상(매핑, 대응)


















*/
