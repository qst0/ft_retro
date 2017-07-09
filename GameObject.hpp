#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP

typedef struct {
	int x;
	int y;
} vec2i;

typedef struct {
	unsigned int x;
	unsigned int y;
} vec2ui;

typedef struct {
	vec2i pos;
	char disp_char;
} player;



class Rect {
 public:
  int x;
  int y;
  int width;
  int length;
};

class GameObject {

	public:
		GameObject();
		void update();
		void activate(int, int);
		void deactivate();
		bool isActive();

		vec2i getPos() const;
		void setPos(vec2i);

	private:
		vec2i pos;
		bool active;
};

class GameObjectField {

	public:
		GameObjectField();
		~GameObjectField();
		void update();
		GameObject* getData() const;
		size_t getCount() const;
		void setBounds(Rect);

	private:
		Rect field_bounds;
		GameObject* object_set;
		size_t		object_count;
};

#endif
