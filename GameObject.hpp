#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

# include "Vec2i.hpp"

class GameObject {

	public:
		GameObject();
		GameObject(GameObject const & src);
		GameObject & operator=(GameObject const & rhs);

		void	updateToLeft();
		void	updateToRight();
		void	activate(int nx, int ny);
		void	deactivate();
		bool	isActive() const; // gets active state 

		Vec2i	getPos() const;
		void	setPos(Vec2i const src);

	protected:
		char	object;
		Vec2i	pos;
		bool	active;
};

#endif
