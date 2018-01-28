#include "System.h"

namespace KIWF {

	System::System() {
		this->video = new Video();
		this->input = new Input();
	}

	System::~System() {}

	void System::setMode(Mode* mode) {
		this->mode = mode;
	}

	Video* System::getVideo() {
		return this->video;
	}

	Input* System::getInput() {
		return this->input;
	}

	void System::runLoop() {
		while(1) {

			if (this->mode != NULL) {
				this->input->fetchInput();

				this->mode->processInput();

				swiWaitForVBlank();

				this->video->swapBuffers();
			}
		}
	}

	// Some functions copied from:
	// http://www.coranac.com/2009/05/dma-vs-arm9-fight/

	//! Copy data from a src to a dst via DMA in a cache/section safe manner.
	/*! The ARM9's DMA doesn't play well with the cache and can't access
	    ITCM or DTCM. This means that a basic DMA copy may not work as
	    expected. This function flushes or invalidates cache if necessary and
	    will only copy if the ranges are accessible.
	    param src   Source pointer.
	    param dst   Destination pointer.
	    param size  Size (in bytes) to copy.
	    return      True if the copy succeeded.
	    note        It's possible I missed some invalid cases, YHBW.
	*/
	bool System::dmaCopySafe(const void *src, void *dst, u32 size) {
	    u32 srca= (u32)src, dsta= (u32)dst;

	    // Check TCMs and BIOS (0x01000000, 0x0B000000, 0xFFFF0000).
	    //# NOTE: probably incomplete checks.
	    if ((srca>>24)==0x01 || (srca>>24)==0x0B || (srca>>24)==0xFF) {
	        return false;
	    }
	    if ((dsta>>24)==0x01 || (dsta>>24)==0x0B || (dsta>>24)==0xFF) {
	        return false;
	    }

	    if ((srca|dsta) & 1) {
	    	// Fail on byte copy.
	        return false;
	    }

	    // FIXME: Does not work, why?
//	    while (REG_DMA3CNT & DMA_BUSY) ;

	    // Write cache back to memory.
	    if ((srca>>24)==0x02) {
	        DC_FlushRange(src, size);
	    }

	    if ((srca|dsta|size) & 3) {
	        dmaCopyHalfWords(3, src, dst, size);
	    } else {
	        dmaCopyWords(3, src, dst, size);
	    }

	    // Set cache of dst range to 'dirty'
	    if ((dsta>>24)==0x02) {
	        DC_InvalidateRange(dst, size);
	    }

	    return true;
	}

	//! Fill a dst with a fill via DMA in a cache/section safe manner.
	/*! The ARM9's DMA doesn't play well with the cache and can't access
	    ITCM or DTCM. This means that a basic DMA fill may not work as
	    expected. This function flushes or invalidates cache if necessary and
	    will only fill if the ranges are accessible.
	    param fill  Fill value.
	    param dst   Destination pointer.
	    param size  Size (in bytes) to copy.
	    return      True if the fill succeeded.
	    note        It's possible I missed some invalid cases, YHBW.
	*/
	bool System::dmaFillSafe(u32 fill, void *dst, u32 size) {
	    u32 dsta= (u32)dst;

	    // Check TCMs and BIOS (0x01000000, 0x0B000000, 0xFFFF0000).
	    //# NOTE: probably incomplete checks.
	    if ((dsta>>24)==0x01 || (dsta>>24)==0x0B || (dsta>>24)==0xFF) {
	        return false;
	    }

	    // Fail on byte fill.
	    if (dsta & 1) {
	        return false;
	    }

	    // FIXME: Does not work, why?
//	    while (REG_DMA3CNT & DMA_BUSY) ;

	    if ((dsta|size) & 3) {
	        dmaFillHalfWords(fill, dst, size);
	    } else {
	        dmaFillWords(fill, dst, size);
	    }

	    // Set cache of dst range to 'dirty'
	    if ((dsta>>24) == 0x02) {
	        DC_InvalidateRange(dst, size);
	    }

	    return true;
	}
}
