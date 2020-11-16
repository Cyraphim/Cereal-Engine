#pragma once

#include <iostream>
#include <map>

// Basic Entity Component System, it is actually just a system of Entities and Components
// ECS is similar to how it works in Unity.

struct Entity;

struct Component
{
	Entity* entity;	

	// Override these to provide functionality

	// Called once in the beginning
	virtual void Start()
	{
	}

	// Called once every frame
	virtual void Update()
	{
	}

	// used for the draw call
	virtual void Draw()
	{
	}
};

struct Entity
{
	public:
		std::string _name;
	private:
		// Component list, do not steal
		std::map<std::string, Component*> _components;
	public:

		Entity()
		{
			_components = std::map<std::string, Component*>();
		}

		void Start()
		{
			for(auto c : _components)
			{
				c.second->Start();
			}
		}

		void Update()
		{
			for (auto c : _components)
			{
				c.second->Update();
			}
		}

		void Draw()
		{
			for (auto c : _components)
			{
				c.second->Draw();
			}
		}
		
		template <typename T>
		T* AddComponent()
		{
			if (_components.count(typeid(T).name()))
			{
				return static_cast<T*>(_components[typeid(T).name()]);
			}
			T* component = new T();
			component->entity = this;
			_components.insert(std::pair<std::string, Component*>(typeid(T).name(), component));

			return static_cast<T*>(_components[typeid(T).name()]);
		}

		// This one just copies the component into the map
		// Had to make it because I'm dumb
		template <typename T>
		T* AddComponent(T* component)
		{
			component->entity = this;
			_components.insert(std::pair<std::string, Component*>(typeid(T).name(), component));
			return static_cast<T*>(_components[typeid(T).name()]);
		}


		template <typename T>
		T* GetComponent()
		{
			std::map<std::string, Component*>::iterator  i = _components.find(typeid(T).name());
			if(i != _components.end())
			{
			return static_cast<T*>(i->second);
			}
			else
			{
				return (T*) NULL;
			}
		}

		template <typename T>
		bool HasComponent()
		{
			std::map<std::string, Component*>::iterator  i = _components.find(typeid(T).name());
			if (i != _components.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		
		// TODO: Get rid of this
		// TODO: Print everything using IMGUI
		void ListAllComponents()
		{
			for (auto c : _components)
			{
				std::cout << (char)26 << (char)26 << c.first << std::endl;
			}
		}
};