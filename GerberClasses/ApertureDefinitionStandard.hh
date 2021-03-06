#ifndef _APERTURE_DEFINITION_STANDARD_H
#define _APERTURE_DEFINITION_STANDARD_H

#include "ApertureDefinition.hh"
#include "StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <memory>

class ApertureDefinitionStandard : public ApertureDefinition {
public:
	ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture);
	ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture,
        yy::location aperture_number_location, yy::location location);
	virtual ~ApertureDefinitionStandard();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<StandardAperture> m_standard_aperture;
};

#endif // _APERTURE_DEFINITION_STANDARD_H
