#pragma once
#define SINGLE(Type) public :\
						static Type* Get_Inst() {\
							static Type pType;\
							return &pType;\
							}\
					  private :\
						Type();\
						~Type();
										