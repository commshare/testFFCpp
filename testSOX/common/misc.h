#pragma once

#include "common/unistr.h"
#include "common/int_types.h"

namespace protocol
{
	typedef		UniString		DATE ;			//	MM-DD-YYYY

	typedef		UniString		DATETIME ;		//	like "Tue May 03 21:51:03 1994"

	typedef		uint32_t		COLOR ;			//	0x00bbggrr 

	enum	FONTEFFECTS{
		FE_BOLD = 1 ,
		FE_ITALIC = 2 ,
		FE_STRIKETHROUGH = 4 ,
		FE_UNDERLINE = 8
	};
	struct	FONT{
		uint32_t		effects ;
		UniString		name ;
		FONT(){		// default ?
			effects = 0 ;
#ifdef WIN32
			name = L"Arial" ;
#endif
		};
		FONT(const FONT & src ){
			effects = src.effects ;
			name = src.name ;
		}
		FONT & operator = (const FONT & src ){
			if( this != & src ){
				effects = src.effects ;
				name = src.name ;
			}
			return * this ;
		}
	};
}