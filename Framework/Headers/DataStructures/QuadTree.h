#pragma once

#include <vector>
#include <set>


//quad tree has its own space
//quad tree space is from 0 to 1

namespace lun
{
	enum class QuadPosition
	{
		downLeft,
		downRight,
		upLeft,
		upRight,
	};

	struct BoundBox
	{
		float minX, maxX;
		float minY, maxY;

		bool overlap(BoundBox &other)
		{
			return (maxX >= other.minX && minX <= other.maxX &&
				maxY >= other.minY && minY <= other.maxY);
		}
		//how much this this AABB overlap another AABB
		float overlapPercentage(BoundBox &other)
		{
			if (contains(other))
			{
				return 1.f;
			}
			if (other.contains(*this))
			{
				return 0.f;
			}
			float xdist1 = abs(maxX - other.minX);
			float xdist2 = abs(minX - other.maxX);
			float ydist1 = abs(maxY - other.minY);
			float ydist2 = abs(minY - other.minY);
			if (xdist2 < xdist1)
			{
				xdist1 = xdist2;
			}
			if (ydist2 < ydist1)
			{
				ydist1 = ydist2;
			}
			return (xdist1 * ydist1) / (abs(other.minX - other.maxX) * abs(other.minY - other.maxY));
		}
		bool contains(BoundBox &other)
		{
			return (other.minX >= minX && other.maxX <= maxX &&
				other.minY >= minY && other.maxY <= maxY);
		}
		bool containsNoBorder(BoundBox &other)
		{
			return (other.minX > minX && other.maxX < maxX &&
				other.minY > minY && other.maxY < maxY);
		}
		bool outsideOf(BoundBox &other)
		{
			return (other.minX <= minX && other.maxX >= maxX &&
				other.minY <= minY && other.maxY >= maxY);
		}
		bool canCoexist(BoundBox &other)
		{
			//return (contains(other));
			//return (other.contains(*this));
			return (!containsNoBorder(other) && !other.containsNoBorder(*this) && overlap(other));
		}
		bool compare(BoundBox &other)
		{
			return (maxX == other.maxX && maxY == other.maxY && minX == other.minX && minY == other.maxY);
		}
		BoundBox() {}
		BoundBox(float _minX, float _minY, float _maxX, float _maxY) : minX(_minX), minY(_minY), maxX(_maxX), maxY(_maxY)
		{};
	};

	template<typename T>
	struct QuadTreeBoundBox
	{
		BoundBox boundBox;
		T *object;
		QuadTreeBoundBox() {}
	};

	template<typename T>
	class QuadTree;

	template<typename T>
	class QuadTreeNode
	{
	public:
		friend QuadTree<T>;
		QuadTreeNode() 
		{
			containedObjects = std::vector<QuadTreeBoundBox<T>>();
			childs[0] = nullptr;
			childs[1] = nullptr;
			childs[2] = nullptr;
			childs[3] = nullptr;
		}

		bool isLeaf()
		{
			return (childs[0] == nullptr && childs[1] == nullptr && childs[2] == nullptr && childs[3] == nullptr);
		}

		void pushDown(QuadTreeBoundBox<T> &element, unsigned int myLayer, unsigned int maxLayer, float startX, float startY, bool isRepush = false)
		{
			float width = 1.f / (float)myLayer;
			float height = width;
			if (!childs[(unsigned int)QuadPosition::downLeft]) childs[(unsigned int)QuadPosition::downLeft] = new QuadTreeNode();
			if (!childs[(unsigned int)QuadPosition::downRight]) childs[(unsigned int)QuadPosition::downRight] = new QuadTreeNode();
			if (!childs[(unsigned int)QuadPosition::upLeft]) childs[(unsigned int)QuadPosition::upLeft] = new QuadTreeNode();
			if (!childs[(unsigned int)QuadPosition::upRight]) childs[(unsigned int)QuadPosition::upRight] = new QuadTreeNode();
			childs[(unsigned int)QuadPosition::downLeft]->push(element, myLayer + 1, maxLayer, startX, startY);
			childs[(unsigned int)QuadPosition::downRight]->push(element, myLayer + 1, maxLayer, startX + width / 2.f, startY);
			childs[(unsigned int)QuadPosition::upLeft]->push(element, myLayer + 1, maxLayer, startX, startY + height / 2.f);
			childs[(unsigned int)QuadPosition::upRight]->push(element, myLayer + 1, maxLayer, startX + width / 2.f, startY + height / 2.f);
		}

		void addElement(QuadTreeBoundBox<T> &element, unsigned int myLayer, unsigned int maxLayer, float startX, float startY, bool isRepush = false)
		{
			bool stillPush = true;
			if (stillPush)
			{
				containedObjects.push_back(element);
			}
		}

		void addElement(QuadTreeBoundBox<T> &element)
		{
			containedObjects.push_back(element);
		}

		void push(QuadTreeBoundBox<T> &element, unsigned int myLayer, unsigned int maxLayer, float startX, float startY, bool isRepush = false)
		{
			float width = 1.f / (float)myLayer;
			float height = width;

			//calculate bound boxes
			BoundBox downLeft(startX, startY, startX + width / 2.f, startY + height / 2.f);
			BoundBox downRight(startX + width / 2.f, startY, startX + width, startY + height / 2.f);
			BoundBox upLeft(startX, startY + height/2.f, startX + width / 2.f, startY + height);
			BoundBox upRight(startX + width / 2.f, startY + height / 2.f, startX + width, startY + height);

			bool hitDownLeft = downLeft.overlap(element.boundBox);
			bool hitDownRight = downRight.overlap(element.boundBox);
			bool hitUpLeft = upLeft.overlap(element.boundBox);
			bool hitUpRight = upRight.overlap(element.boundBox);

			if (hitDownLeft && hitDownRight && hitUpLeft && hitUpRight && containedObjects.size() == 0)
			{
				//hits all, put in contained objects
				addElement(element, myLayer, maxLayer, startX, startY, isRepush);
			}
			else
			{
				if (hitDownLeft)
				{
					if (childs[(unsigned int)QuadPosition::downLeft] == nullptr)
					{
						childs[(unsigned int)QuadPosition::downLeft] = new QuadTreeNode();
					}
					childs[(unsigned int)QuadPosition::downLeft]->push(element, myLayer + 1, maxLayer, downLeft.minX, downLeft.minY);
				}
				if (hitDownRight)
				{
					if (childs[(unsigned int)QuadPosition::downRight] == nullptr)
					{
						childs[(unsigned int)QuadPosition::downRight] = new QuadTreeNode();
					}
					childs[(unsigned int)QuadPosition::downRight]->push(element, myLayer + 1, maxLayer, downRight.minX, downRight.minY);
				}
				if (hitUpLeft)
				{
					if (childs[(unsigned int)QuadPosition::upLeft] == nullptr)
					{
						childs[(unsigned int)QuadPosition::upLeft] = new QuadTreeNode();
					}
					childs[(unsigned int)QuadPosition::upLeft]->push(element, myLayer + 1, maxLayer, upLeft.minX, upLeft.minY);
				}
				if (hitUpRight)
				{
					if (childs[(unsigned int)QuadPosition::upRight] == nullptr)
					{
						childs[(unsigned int)QuadPosition::upRight] = new QuadTreeNode();
					}
					childs[(unsigned int)QuadPosition::upRight]->push(element, myLayer + 1, maxLayer, upRight.minX, upRight.minY);
				}
			}
		}

		void pushVolume(QuadTreeBoundBox<T> &element, unsigned int myLayer, unsigned int maxLayer, float startX, float startY, float volumeDetail = 0.5f)
		{
			//check if at limit
			if (myLayer >= maxLayer)
			{
				addElement(element);
				return;
			}

			float width = 1.f / (float)myLayer;
			float height = width;

			//calculate bound boxes
			BoundBox downLeft(startX, startY, startX + width / 2.f, startY + height / 2.f);
			BoundBox downRight(startX + width / 2.f, startY, startX + width, startY + height / 2.f);
			BoundBox upLeft(startX, startY + height / 2.f, startX + width / 2.f, startY + height);
			BoundBox upRight(startX + width / 2.f, startY + height / 2.f, startX + width, startY + height);

			//calculate volume percentages
			float volDownLeft  = element.boundBox.overlapPercentage(downLeft);
			float volDownRight = element.boundBox.overlapPercentage(downRight);
			float volUpLeft = element.boundBox.overlapPercentage (upLeft);
			float volUpRight = element.boundBox.overlapPercentage(upRight);
			
			//down left 
			if (volDownLeft >= volumeDetail)
			{
				if (childs[(unsigned int)QuadPosition::downLeft] == nullptr)
					childs[(unsigned int)QuadPosition::downLeft] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::downLeft]->addElement(element);
			}
			else if (volDownLeft > 0.f)
			{
				if (childs[(unsigned int)QuadPosition::downLeft] == nullptr)
					childs[(unsigned int)QuadPosition::downLeft] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::downLeft]->pushVolume(element, myLayer + 1, maxLayer, downLeft.minX, downLeft.minY, volumeDetail);
			}

			//down right
			if (volDownRight >= volumeDetail)
			{
				if (childs[(unsigned int)QuadPosition::downRight] == nullptr)
					childs[(unsigned int)QuadPosition::downRight] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::downRight]->addElement(element);
			}
			else if (volDownRight > 0.f)
			{
				if (childs[(unsigned int)QuadPosition::downRight] == nullptr)
					childs[(unsigned int)QuadPosition::downRight] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::downRight]->pushVolume(element, myLayer + 1, maxLayer, downRight.minX, downRight.minY, volumeDetail);
			}

			//up left 
			if (volUpLeft >= volumeDetail)
			{
				if (childs[(unsigned int)QuadPosition::upLeft] == nullptr)
					childs[(unsigned int)QuadPosition::upLeft] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::upLeft]->addElement(element);
			}
			else if (volUpLeft > 0.f)
			{
				if (childs[(unsigned int)QuadPosition::upLeft] == nullptr)
					childs[(unsigned int)QuadPosition::upLeft] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::upLeft]->pushVolume(element, myLayer + 1, maxLayer, upLeft.minX, upLeft.minY, volumeDetail);
			}

			//up right
			if (volUpRight >= volumeDetail)
			{
				if (childs[(unsigned int)QuadPosition::upRight] == nullptr)
					childs[(unsigned int)QuadPosition::upRight] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::upRight]->addElement(element);
			}
			else if (volUpRight > 0.f)
			{
				if (childs[(unsigned int)QuadPosition::upRight] == nullptr)
					childs[(unsigned int)QuadPosition::upRight] = new QuadTreeNode<T>();
				childs[(unsigned int)QuadPosition::upRight]->pushVolume(element, myLayer + 1, maxLayer, upRight.minX, upRight.minY, volumeDetail);
			}
			
		}

		void search(std::set<T*> &ret, BoundBox &boundBox, unsigned int myLayer, unsigned int maxLayer, float startX, float startY)
		{
			for (unsigned int it = 0; it < containedObjects.size(); ++it)
			{
				ret.insert(containedObjects[it]->object);
			}

			float width = 1.f / (float)myLayer;
			float height = width;

			//calculate bound boxes
			BoundBox downLeft(startX, startY, startX + width / 2.f, startY + height / 2.f);
			BoundBox downRight(startX + width / 2.f, startY, startX + width, startY + height / 2.f);
			BoundBox upLeft(startX, startY + height / 2.f, startX + width / 2.f, startY + height);
			BoundBox upRight(startX + width / 2.f, startY + height / 2.f, startX + width, startY + height);

			bool hitDownLeft = downLeft.overlap(boundBox);
			bool hitDownRight = downRight.overlap(boundBox);
			bool hitUpLeft = upLeft.overlap(boundBox);
			bool hitUpRight = upRight.overlap(boundBox);

			if (hitDownLeft)
			{
				if (childs[(unsigned int)QuadPosition::downLeft] != nullptr)
				{
					childs[(unsigned int)QuadPosition::downLeft]->search(ret, boundBox, myLayer + 1, maxLayer, downLeft.minX, downLeft.minY);
				}
			}

			if (hitDownRight)
			{
				if (childs[(unsigned int)QuadPosition::downRight] != nullptr)
				{
					childs[(unsigned int)QuadPosition::downRight]->search(ret, boundBox, myLayer + 1, maxLayer, downRight.minX, downRight.minY);
				}
			}

			if (hitUpLeft)
			{
				if (childs[(unsigned int)QuadPosition::upLeft] != nullptr)
				{
					childs[(unsigned int)QuadPosition::upLeft]->search(ret, boundBox, myLayer + 1, maxLayer, upLeft.minX, upLeft.minY);
				}
			}

			if (hitUpRight)
			{
				if (childs[(unsigned int)QuadPosition::upRight] != nullptr)
				{
					childs[(unsigned int)QuadPosition::upRight]->search(ret, boundBox, myLayer + 1, maxLayer, upRight.minX, upRight.minY);
				}
			}
		}

		void updateTree(unsigned int myLayer, unsigned int maxLayer, float startX, float startY, bool isRepush = false)
		{
			
		}
	private:
		//container of (collision) objects constained withing this node of the tree
		std::vector<QuadTreeBoundBox<T>> containedObjects;
		
		//other nodes
		QuadTreeNode<T> *childs[4];
	};

	//main quad tree class,
	//is an interface that uses quad tree nodes
	template<typename T>
	class QuadTree
	{
	public:
		QuadTree() 
		{
			baseNode = QuadTreeNode<T>();
		}
		QuadTree(unsigned int maxDepth, float volumeDetail)
		{
			this->maxDepth = maxDepth;
			this->volumeDetail = volumeDetail;
			baseNode = QuadTreeNode<T>();
		}
		//del
		~QuadTree()
		{
			deleteNode(&baseNode);
		}
		//cpy
		QuadTree(const QuadTree<T> &other)
		{
			QuadTreeNode<T> *startNode = cpyNode(other.baseNode);
			baseNode = *startNode;
			delete startNode;
			maxElementsPerNode = other.maxElementsPerNode;
			maxDepth = other.maxDepth;
		}
		QuadTree<T> &operator=(const QuadTree<T> &other)
		{
			QuadTreeNode<T> *startNode = cpyNode(other.baseNode);
			baseNode = *startNode;
			delete startNode;
			maxElementsPerNode = other.maxElementsPerNode;
			maxDepth = other.maxDepth;
			return *this;
		}
		
		void push(QuadTreeBoundBox<T> element)
		{
			//baseNode.push(element, 1, maxDepth, 0.f, 0.f);
			//baseNode.updateTree(1, maxDepth, 0.f, 0.f);
			baseNode.pushVolume(element, 1, maxDepth, 0.f, 0.f, volumeDetail);
		}

		void push(float minX, float minY, float maxX, float maxY, T *object)
		{
			QuadTreeBoundBox<T> pushElement;
			pushElement.boundBox.minX = minX;
			pushElement.boundBox.maxX = maxX;
			pushElement.boundBox.minY = minY;
			pushElement.boundBox.maxY = maxY;
			pushElement.object = object;
			push(pushElement);
		}
		
		void update()
		{
			baseNode.updateTree(1, 10, 0.f, 0.f);
		}

		std::vector<T*> get(BoundBox box)
		{
			std::set<T*> retGet = std::set<T*>();
			baseNode.search(retGet, box, 1, maxDepth, 0.f, 0.f);
			std::vector<T*> ret = std::vector<T*>(retGet.size());
			for (auto it = retGet.begin(); it != retGet.end(); it++)
			{
				ret.push_back(*it);
			}
			return ret;
		}

	private:
		QuadTreeNode<T> *cpyNode(QuadTreeNode<T> &other)
		{
			QuadTreeNode<T> *ret = new QuadTreeNode<T>(other);
			for (unsigned int it = 0; it < 4; ++it)
			{
				if (other.childs[it] != nullptr)
				{
					ret->childs[it] = cpyNode(other.childs[it]);
				}
			}
			return ret;
		}

		void deleteNode(QuadTreeNode<T> *other)
		{
			for (unsigned int it = 0; it < 4; ++it)
			{
				if (other->childs[it] != nullptr)
				{
					deleteNode(other->childs[it]);
				}
			}
			delete other;
		}

	private:
		//start of the tree
		QuadTreeNode<T> baseNode;

		//the hitboxed/elents one node in the tree should contain
		unsigned int maxElementsPerNode = 1;
		unsigned int maxDepth = 10;
		float volumeDetail = 0.5f;
	};
}