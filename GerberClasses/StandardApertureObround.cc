#include "StandardApertureObround.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "../location.hh"

#include <iostream>
#include <memory>

StandardApertureObround::StandardApertureObround(double x_size, double y_size, double hole_diameter) :
    m_x_size(x_size), m_y_size(y_size), m_hole_diameter(hole_diameter), m_has_hole(true)
{}

StandardApertureObround::StandardApertureObround(double x_size, double y_size) :
    m_x_size(x_size), m_y_size(y_size), m_hole_diameter(0.0), m_has_hole(false)
{}

StandardApertureObround::StandardApertureObround(double x_size, double y_size, double hole_diameter,
    yy::location x_size_location, yy::location y_size_location, yy::location hole_diameter_location,
    yy::location location) :
            m_x_size(x_size), m_y_size(y_size), m_hole_diameter(hole_diameter), m_has_hole(true),
            m_x_size_location(x_size_location), m_y_size_location(y_size_location),
            m_hole_diameter_location(hole_diameter_location), m_location(location)
{}

StandardApertureObround::StandardApertureObround(double x_size, double y_size,
    yy::location x_size_location, yy::location y_size_location, yy::location location) :
        m_x_size(x_size), m_y_size(y_size), m_hole_diameter(0.0), m_has_hole(false),
        m_x_size_location(x_size_location), m_y_size_location(y_size_location),
        m_location(location)
{}

StandardApertureObround::~StandardApertureObround()
{}

Gerber::SemanticValidity StandardApertureObround::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // Width and height must be > 0
    if (m_x_size <= 0.0) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_x_size_location,
            "X-size for obround-type standard aperture must be > 0");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    if (m_y_size <= 0.0) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_y_size_location,
            "Y-size for obround-type standard aperture must be > 0");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // If the aperture has a hole, it must have a diameter >= 0, and the hole must not be bigger
    // than the aperture itself.  We'll warn for holes of diameter 0 (since it's not invalid per
    // the spec, but it's redundant, since you can just omit the hole), and we'll return a fatal
    // error if the hole is bigger than the aperture, because this creates a zero size aperture
    // in an improper way
    if (m_has_hole) {
        if (m_hole_diameter < 0.0) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_hole_diameter_location,
                "Hole diameter for obround-type standard aperture must be >= 0");
            issue_list.add_issue(issue);
            return issue.severity();
        } else if (m_hole_diameter == 0.0) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
                m_hole_diameter_location,
                "Hole diameter of 0 for obround-type standard aperture is redundant (hole diameter can be omitted)");
            issue_list.add_issue(issue);
        }

        // Hole obstructs entire aperture if its diameter is >= x_size + y_size
        // (unless x_size == y_size, in which case the aperture is a circle,
        // and either x_size or y_size is the diameter
        if (((m_x_size == m_y_size) && (m_hole_diameter >= m_x_size)) || (m_hole_diameter >= (m_x_size + m_y_size))) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_hole_diameter_location,
                "Hole in obround-type standard aperture must not be larger than the aperture itself");
            issue_list.add_issue(issue);
            return issue.severity();
        }
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::shared_ptr<StandardAperture> StandardApertureObround::do_clone()
{
    return std::make_shared<StandardApertureObround>(*this);
}

std::ostream& StandardApertureObround::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Obround (@" << m_location << ")" << std::endl;
	os << "X Size: " << m_x_size << " (@" << m_x_size_location << ")" << std::endl;
	os << "Y Size: " << m_y_size << " (@" << m_y_size_location << ")" << std::endl;
	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << " (@" << m_hole_diameter_location << ")" << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	return os;
}
