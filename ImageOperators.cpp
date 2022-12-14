#include "ImageOperators.h"
#include <emmintrin.h>

#pragma warning(disable:4018) // signed/unsigned mismatch

#define EMMX_BLEND(comp) \
	t = _mm_loadu_si128((__m128i *) pDst[(comp)]);                      \
	d0 = _mm_unpacklo_epi8(t, zero);                                    \
	d1 = _mm_unpackhi_epi8(t, zero);                                    \
	t = _mm_loadu_si128((__m128i *) pSrc[(comp)]);                      \
	_mm_storeu_si128((__m128i *) pDst[(comp)], _mm_packus_epi16(_mm_srli_epi16(_mm_add_epi16(_mm_mullo_epi16(_mm_unpacklo_epi8(t, zero), a0), _mm_mullo_epi16(_mm_sub_epi16(ff, a0), d0)), 8), _mm_srli_epi16(_mm_add_epi16(_mm_mullo_epi16(_mm_unpackhi_epi8(t, zero), a1), _mm_mullo_epi16(_mm_sub_epi16(ff, a1), d1)), 8)))                      

void blitBlend( UCImg &src, UCImg &dst, unsigned int dstXOffset, unsigned int dstYOffset, SimdMode simdMode)
{
	if (src.spectrum() != 4) throw cimg_library::CImgException("blitBlend: Src image is missing ALPHA channel");

	// calcualte our SIMD blend area (defined by X0, Y0 to X1, Y1). Take into account alignment restrictions;

	unsigned int X1 = src.width() + dstXOffset;
	if (X1 > dst.width()) X1 = dst.width();
	unsigned int X0 = dstXOffset;

	unsigned int Y1 = src.height() + dstYOffset;
	if (Y1 > dst.height()) Y1 = dst.height();

	unsigned int Y0 = dstYOffset;
	// TODO: Y0 & Y1 need to be aligned.


	for (unsigned int y = Y0, srcLine = 0; y < Y1; y++, srcLine++) {
		unsigned char *pSrc[4];
		pSrc[0] = src.data(0, srcLine, 0, 0);
		pSrc[1] = src.data(0, srcLine, 0, 1);
		pSrc[2] = src.data(0, srcLine, 0, 2);
		pSrc[3] = src.data(0, srcLine, 0, 3);

		unsigned char *pDst[4];
		pDst[0] = dst.data(X0, y, 0, 0);
		pDst[1] = dst.data(X0, y, 0, 1);
		pDst[2] = dst.data(X0, y, 0, 2);
		pDst[3] = dst.data(X0, y, 0, 3); //added this line so that alpha of destination could be used

		short ffconst[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
		//*** __m128i maps to 128-bit XMM registers
		__m128i ff = _mm_loadu_si128((__m128i *)ffconst);

		if (simdMode == SIMD_EMMX) {
			for (unsigned x = X0; x < X1; x += 16) {
				__asm {
					//This block sets the pointer which will be used for the alpha blend factor
					pxor xmm0, xmm0 // xmm0 <- 0
					mov eax, dword ptr [pDst + 12] // changed this from pSrc to pDst to blend with destination image.
					movdqu xmm1, [eax]; xmm1 <- *pDst[3] // changed this from pSrc to pDst to blend with destination image.
					movdqa xmm2, xmm1; 
					punpcklbw xmm2, xmm0; // xmm2 <- a0, 16bit
					movdqa xmm3, xmm1;
					punpckhbw xmm3, xmm0; // xxm3 <- a1, 16bit

					// blending the red;
					// load d0
					// uses pDst + 0 to get the red value
					mov eax, dword ptr[pDst + 0]; 
					movdqu xmm1, [eax]; // xmm1 = pDst[0]
					movdqa xmm6, xmm1;
					punpcklbw xmm6, xmm0; // xmm6 <- pDst[0] low 16bit
					movdqa xmm7, xmm1;
					punpckhbw xmm7, xmm0; // xmm7 <- pDst[0] high, 16 bit
					// load the ff constant
					movdqu xmm4, [ffconst]; // xmm4 <- ff
					movdqa xmm5, xmm4; 
					psubw  xmm5, xmm2; // xmm5 = ff - a0
					pmullw xmm6, xmm5; // xmm6 = (ff - a0) * d0;
					// now for the upper bits
					movdqa xmm5, xmm4;
					psubw  xmm5, xmm3; // xmm5 = ff - a1
					pmullw xmm7, xmm5; // xmm7 = (ff - a1) * d1;
					// load the source;
					mov eax, dword ptr[pSrc + 0];
					movdqu xmm1, [eax]; // xmm1 = pSrc[0]
					// low bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpcklbw xmm5, xmm0; // xmm5 = pSrc[0], low, 16 bit;
					pmullw xmm5, xmm2; // xmm5 = s0 * a0;
					paddw xmm6, xmm5; // xmm6 = s0 * a0 + (ff - a0) * d0;
					// high bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpckhbw xmm5, xmm0;
					pmullw xmm5, xmm3; // xmm5 = s1 * a1
					paddw xmm7, xmm5; // xmm7 = s1 * a1 + (ff - a1) * d1;
					// shift the results;
					// this is a bit shift by 8
					psrlw xmm6, 8;
					psrlw xmm7, 8;
					// pack back
					packuswb xmm6, xmm7; // xmm6 <- xmm6{}xmm7 low bits;
					mov eax, dword ptr [pDst + 0];
					movdqu [eax], xmm6; // done for this component;

					// blending the green;
					// load d0
					// uses pDst + 4 to get the green value
					mov eax, dword ptr[pDst + 4]; 
					movdqu xmm1, [eax]; // xmm1 = pDst[0]
					movdqa xmm6, xmm1;
					punpcklbw xmm6, xmm0; // xmm6 <- pDst[0] low 16bit
					movdqa xmm7, xmm1;
					punpckhbw xmm7, xmm0; // xmm7 <- pDst[0] high, 16 bit
					// load the ff constant
					movdqu xmm4, [ffconst]; // xmm4 <- ff
					movdqa xmm5, xmm4; 
					psubw  xmm5, xmm2; // xmm5 = ff - a0
					pmullw xmm6, xmm5; // xmm6 = (ff - a0) * d0;
					// now for the upper bits
					movdqa xmm5, xmm4;
					psubw  xmm5, xmm3; // xmm5 = ff - a1
					pmullw xmm7, xmm5; // xmm7 = (ff - a1) * d1;
					// load the source;
					mov eax, dword ptr[pSrc + 4];
					movdqu xmm1, [eax]; // xmm1 = pSrc[0]
					// low bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpcklbw xmm5, xmm0; // xmm5 = pSrc[0], low, 16 bit;
					pmullw xmm5, xmm2; // xmm5 = s0 * a0;
					paddw xmm6, xmm5; // xmm6 = s0 * a0 + (ff - a0) * d0;
					// high bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpckhbw xmm5, xmm0;
					pmullw xmm5, xmm3; // xmm5 = s1 * a1
					paddw xmm7, xmm5; // xmm7 = s1 * a1 + (ff - a1) * d1;
					// shift the results;
					// this is a bit shift by 8
					psrlw xmm6, 8;
					psrlw xmm7, 8;
					// pack back
					packuswb xmm6, xmm7; // xmm6 <- xmm6{}xmm7 low bits;
					mov eax, dword ptr [pDst + 4];
					movdqu [eax], xmm6; // done for this component;

					// blending the blue;
					// load d0
					// uses pDst + 8 to get the blue value
					mov eax, dword ptr[pDst + 8]; 
					movdqu xmm1, [eax]; // xmm1 = pDst[0]
					movdqa xmm6, xmm1;
					punpcklbw xmm6, xmm0; // xmm6 <- pDst[0] low 16bit
					movdqa xmm7, xmm1;
					punpckhbw xmm7, xmm0; // xmm7 <- pDst[0] high, 16 bit
					// load the ff constant
					movdqu xmm4, [ffconst]; // xmm4 <- ff
					movdqa xmm5, xmm4; 
					psubw  xmm5, xmm2; // xmm5 = ff - a0
					pmullw xmm6, xmm5; // xmm6 = (ff - a0) * d0;
					// now for the upper bits
					movdqa xmm5, xmm4;
					psubw  xmm5, xmm3; // xmm5 = ff - a1
					pmullw xmm7, xmm5; // xmm7 = (ff - a1) * d1;
					// load the source;
					mov eax, dword ptr[pSrc + 8];
					movdqu xmm1, [eax]; // xmm1 = pSrc[0]
					// low bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpcklbw xmm5, xmm0; // xmm5 = pSrc[0], low, 16 bit;
					pmullw xmm5, xmm2; // xmm5 = s0 * a0;
					paddw xmm6, xmm5; // xmm6 = s0 * a0 + (ff - a0) * d0;
					// high bits of pSrc[0]
					movdqa xmm5, xmm1;
					punpckhbw xmm5, xmm0;
					pmullw xmm5, xmm3; // xmm5 = s1 * a1
					paddw xmm7, xmm5; // xmm7 = s1 * a1 + (ff - a1) * d1;
					// shift the results;
					// this is a bit shift by 8
					psrlw xmm6, 8;
					psrlw xmm7, 8;
					// pack back
					packuswb xmm6, xmm7; // xmm6 <- xmm6{}xmm7 low bits;
					mov eax, dword ptr [pDst + 8];
					movdqu [eax], xmm6; // done for this component;
				};
				pSrc[0] += 16;
				pSrc[1] += 16;
				pSrc[2] += 16;
				pSrc[3] += 16;

				pDst[0] += 16;
				pDst[1] += 16;
				pDst[2] += 16;
				pDst[3] += 16; //added this for destination alpha.
			}
		} else if (simdMode == SIMD_NONE) {
			for (unsigned int x = X0; x < X1; x++) {
				short diff; // short int for difference between source and destination
				short tmp; // short int for storing a temporary value of destination times difference (and bit shifted by 8)

				diff = *pSrc[0] - *pDst[0]; // calculates difference between source and destination
				tmp = short(*pDst[3] * diff) >> 8; // changed this from pSrc to pDst to use destination alpha.
				*pDst[0] = tmp + *pDst[0]; // assigns destination new value of temp plus destination

				diff = *pSrc[1] - *pDst[1]; // calculates difference between source and destination
				tmp = short(*pDst[3] * diff) >> 8; // changed this from pSrc to pDst to use destination alpha.
				*pDst[1] = tmp + *pDst[1]; // assigns destination new value of temp plus destination

				diff = *pSrc[2] - *pDst[2]; // calculates difference between source and destination
				tmp = short(*pDst[3] * diff) >> 8; // changed this from pSrc to pDst to use destination alpha.
				*pDst[2] = tmp + *pDst[2]; // assigns destination new value of temp plus destination

				pSrc[0] += 1;
				pSrc[1] += 1;
				pSrc[2] += 1;
				pSrc[3] += 1;

				pDst[0] += 1;
				pDst[1] += 1;
				pDst[2] += 1;
				pDst[3] += 1; //added this for destination alpha.
			}
		} else if (simdMode == SIMD_EMMX_INTRINSICS) {

			for (unsigned x = X0; x < X1; x += 16) {
				register __m128i s0, s1, d0, d1, a0, a1, r0, r1, zero; // stores several variables in register process
				register __m128i diff0, tmp0, diff1, tmp1, t; // several more variables in register
				zero = _mm_setzero_si128(); // runs with all elements set to 0
				// load alpha
				t = _mm_loadu_si128((__m128i *) pDst[3]); //changed this from pSrc to pDst to use destination alpha.
				a0 = _mm_unpacklo_epi8(t, zero); // unpacks and interleaves 8-bit integers from low half
				a1 = _mm_unpackhi_epi8(t, zero); // unpacks and interleaves 8-bit integers from high half

				// function calls to do the blending for each colour.
			    EMMX_BLEND(0);
				EMMX_BLEND(1);
				EMMX_BLEND(2);

				pSrc[0] += 16;
				pSrc[1] += 16;
				pSrc[2] += 16;
				pSrc[3] += 16;

				pDst[0] += 16;
				pDst[1] += 16;
				pDst[2] += 16;
				pDst[3] += 16; //added this for destination alpha.
			}
		}

	}
}
