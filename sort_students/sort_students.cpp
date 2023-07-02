#include "sort_students.h"

bool CompByName(Student first_student, Student second_student) {
    if (first_student.last_name != second_student.last_name) {
        return first_student.last_name < second_student.last_name;
    } else if (first_student.name != second_student.name) {
        return first_student.name < second_student.name;
    } else if (first_student.birth_date.year != second_student.birth_date.year) {
        return first_student.birth_date.year < second_student.birth_date.year;
    } else if (first_student.birth_date.month != second_student.birth_date.month) {
        return first_student.birth_date.month < second_student.birth_date.month;
    } else {
        return first_student.birth_date.day < second_student.birth_date.day;
    }
}

bool CompByDate(Student first_student, Student second_student) {
    if (first_student.birth_date.year != second_student.birth_date.year) {
        return first_student.birth_date.year < second_student.birth_date.year;
    } else if (first_student.birth_date.month != second_student.birth_date.month) {
        return first_student.birth_date.month < second_student.birth_date.month;
    } else if (first_student.birth_date.day != second_student.birth_date.day) {
        return first_student.birth_date.day < second_student.birth_date.day;
    } else if (first_student.last_name != second_student.last_name) {
        return first_student.last_name < second_student.last_name;
    } else {
        return first_student.name < second_student.name;
    }
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    switch (sort_kind) {
        case SortKind::Name:
            sort(students.begin(), students.end(), CompByName);
            break;
        case SortKind::Date:
            sort(students.begin(), students.end(), CompByDate);
            break;
    }
}
