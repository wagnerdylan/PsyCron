
#include "PsyTrack.hh"
#include "PsyCron.hh"

namespace psycron {
	UIIL& PsyTrackBase::get_user_parameters(){
		return m_hold_os->get_user_parameters();
	}
}