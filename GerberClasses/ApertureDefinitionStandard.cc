#include "ApertureDefinitionStandard.hh"
#include "StandardAperture.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <string>

ApertureDefinitionStandard::ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture) : ApertureDefinition(aperture_number),
																																	m_standard_aperture(standard_aperture)
{}

ApertureDefinitionStandard::~ApertureDefinitionStandard()
{}

Gerber::SemanticValidity ApertureDefinitionStandard::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    Gerber::SemanticValidity aperture_validity = m_standard_aperture->check_semantic_validity();

    // Only error out here if the standard definition returned a fatal error
    // Else, we'll keep going, and return any warnings or deprecations after
    // checking other stuff that could be fatal
    if (aperture_validity == Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL) {
        return aperture_validity;
    }

    // Attempt to add this aperture into the aperture dictionary of the graphics state
    // If this fails, it means an aperture with this id has already been defined, which
    // is a fatal error
    if (!graphics_state.define_aperture(m_aperture_number, m_standard_aperture->clone())) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    return aperture_validity;
}

std::ostream& ApertureDefinitionStandard::do_print(std::ostream& os) const
{
	os << "Standard Aperture Definition: " << m_aperture_number << std::endl;
	os << *m_standard_aperture;
	return os;
}
