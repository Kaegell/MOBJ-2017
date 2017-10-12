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
			static int count;

		public :
			Box();
			Box(const std::string name, long x1, long y1, long x2, long y2);
			Box(const  Box& other);

			~Box();


			inline std::string getName() const { return name_; }

			inline long getX1() const { return x1_; }

			inline long getY1() const { return y1_; }
			
			inline long getX2() const { return x2_; }
		
			inline long getY2() const { return y2_; }
	
			inline long getWidth() const { return x2_ - x1_; }

			inline long getHeight() const { return y2_ - y1_; }

			static int getAllocateds() { return count; }

			inline bool isEmpty() const { 
				return (x1_ == x2_) || (y1_ == y2_); 
			}

			bool intersect(const Box&) const;
			void print(std::ostream& out) const;
			void makeEmpty();
			void inflate (long dxy);
			void inflate (long dx, long dy);
			void inflate(long dx1, long dy1, long dx2, long dy2);
			Box getIntersection(Box& other);
			Box operator&&(Box& other);

	};
}
#endif
