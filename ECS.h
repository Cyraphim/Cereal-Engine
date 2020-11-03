#pragma once

#include <iostream>
#include <map>

struct Entity;

struct Component
{
	Entity* entity;	

	virtual void Start()
	{
	}

	virtual void Update()
	{
	}

	virtual void Draw()
	{
	}
};

struct Entity
{
	public:
		std::string _name;
	private:
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

		

		void ListAllComponents()
		{
			for (auto c : _components)
			{
				std::cout << (char)26 << (char)26 << c.first << std::endl;
			}
		}
};