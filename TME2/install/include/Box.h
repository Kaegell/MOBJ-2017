#ifndef _BOX_H
#define _BOX_H
namespace tme2
{
	class Box 
	{
		private :
			std::string name_;
			long x1_;
			long y1_;
			long x2_;
			long y2_;

		public :
			Box();
			Box(const std::string name, long x1, long y1, long x2, long y2);
			Box(const  Box& other);

			~Box();

			std::string getName() const;
			long getX1() const;
			long getY1() const;
			long getX2() const;
			long getY2() const;
			long getWidth() const;
			long getHeight() const;
			bool isEmpty() const;
			bool intersect(const Box&) const;
			void print(std::ostream& out) const;

			void makeEmpty();
			void inflate (long dxy);
			void inflate (long dx, long dy);
			void inflate(long dx1, long dy1, long dx2, long dy2);
			Box getIntersection(Box& other);

	};
}
#endif
