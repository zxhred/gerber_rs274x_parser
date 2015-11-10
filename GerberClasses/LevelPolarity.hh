#ifndef _LEVEL_POLARITY_H
#define _LEVEL_POLARITY_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

class LevelPolarity : public Command {
public:
	LevelPolarity(Gerber::LevelPolarityType polarity);
	virtual ~LevelPolarity();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	Gerber::LevelPolarityType m_polarity;
};

#endif // _LEVEL_POLARITY_H