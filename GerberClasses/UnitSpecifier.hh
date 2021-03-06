#ifndef _UNIT_SPECIFIER_H
#define _UNIT_SPECIFIER_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>

class UnitSpecifier : public Command {
public:
	UnitSpecifier(Gerber::UnitType unit_type);
	UnitSpecifier(Gerber::UnitType unit_type, yy::location location);
	virtual ~UnitSpecifier();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	Gerber::UnitType m_unit_type;
	yy::location m_location;
};

#endif // _UNIT_SPECIFIER_H
