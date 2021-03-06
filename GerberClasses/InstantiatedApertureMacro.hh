/*
 * InstantiatedApertureMacro.hh
 *
 *  Created on: Nov 11, 2015
 *      Author: abamberger
 */

#ifndef _INSTANTIATED_APERTURE_MACRO_H
#define _INSTANTIATED_APERTURE_MACRO_H

#include "InstantiatedApertureMacroPrimitive.hh"
#include "Aperture.hh"
#include "GlobalDefs.hh"

#include <memory>
#include <list>

class InstantiatedApertureMacro : public Aperture {
public:
    InstantiatedApertureMacro();
    virtual ~InstantiatedApertureMacro();

    void add_instantiated_macro_content(std::shared_ptr<InstantiatedApertureMacroPrimitive> instantiated_primitive);

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity();

    std::list<std::shared_ptr<InstantiatedApertureMacroPrimitive> > m_macro_content;
};

#endif // _INSTANTIATED_APERTURE_MACRO_H
