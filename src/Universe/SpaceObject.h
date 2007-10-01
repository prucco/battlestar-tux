/* SpaceObject.h
 *
 * Copyright 2007 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef SPACEOBJECT_H_
#define SPACEOBJECT_H_

#include "ListItem.h"
#include "tinyxml.h"


/* A SpaceObject is any object, or group of objects, in space.
 * This could be a planet, a solar system, or even a galaxy.
 * 
 * Very little data about the SpaceObject is stored statically, because it can be
 * generated procedurally.  Any substantial overhead can be trimmed later.
 */
class SpaceObject : public ListItem {
	public:
				SpaceObject();
				virtual ~SpaceObject();

				// Add the object configuration to the given XML node.
				virtual void toXML( TiXmlElement* );

				// Unlike objects that appear during battles, it is not as
				// critical that these objects never skip.  For that reason,
				// they don't need to be as robust about updating their status.
				virtual void Update() {};

				virtual void Draw() {};

				// We need to know the size of this object when positioning it
				// near other objects in an interface.
				virtual float getRadius() { return 0; }

				// We need to know the mass of this object when determining
				// velocities and orbits.
				virtual float getMass() { return mass; }

	protected:
				// How much do we want to scale the speed of the universe?
				// Watching a solar system in real-time is very boring.
				// ~ 1 earth year = 20 seconds
				static const float UNIVERSE_SPEED = 1577880;

				// Gravitational Constant - all bodies with mass attract each other.
				static const float GRAVITATIONAL_CONSTANT = 0.0000000000667428; 

				// All objects need to have mass.
				float mass;

	private:
				SpaceObject( const SpaceObject & );
				const SpaceObject & operator= ( const SpaceObject & );
};



inline std::ostream & operator<<( std::ostream & out, SpaceObject o ) {
	out << &o;
	return out;
}


inline std::ostream & operator<<( std::ostream & out, SpaceObject* o ) {
	TiXmlElement node( "Space_Object" );
	o->toXML( &node );

	out << node;
	return out;
}


#endif /*SPACEOBJECT_H_*/
