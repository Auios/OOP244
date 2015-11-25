#ifndef _SICT_ENROLLMENT_H_
#define _SICT_ENROLLMENT_H_
namespace sict
{
	class Enrollment
	{
	private:
		char _name[31];
		char _code[11];
		int _year;
		int _semester;
		int _slot;
		bool _enrolled;
	public:
		Enrollment();
		Enrollment(const char* _name, const char* _code, int _year, int _semester, int _slot);
		void display(bool nameOnly = false)const;
		bool valid()const;
		void setEmpty();
		bool isEnrolled() const;
		void set(const char* _name, const char* _code, int _year, int _semester, int _slot, bool _enrolled = false);
		bool hasConflict(const Enrollment& other) const;
	};
}
#endif