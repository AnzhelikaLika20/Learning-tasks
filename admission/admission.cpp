#include "admission.h"

#include <algorithm>

bool CompApplicant(const Applicant* student1, const Applicant* student2) {
    if (student1->points != student2->points) {
        return student1->points > student2->points;
    } else if (student1->student.birth_date.year != student2->student.birth_date.year) {
        return student1->student.birth_date.year < student2->student.birth_date.year;
    } else if (student1->student.birth_date.month != student2->student.birth_date.month) {
        return student1->student.birth_date.month < student2->student.birth_date.month;
    } else if (student1->student.birth_date.day != student2->student.birth_date.day) {
        return student1->student.birth_date.day < student2->student.birth_date.day;
    }
    return student1->student.name > student2->student.name;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicants_pointers;
    for (size_t i = 0; i < applicants.size(); ++i) {
        applicants_pointers.push_back(&(applicants[i]));
    }
    std::vector<University> universities_copy(universities);
    sort(applicants_pointers.begin(), applicants_pointers.end(), CompApplicant);
    AdmissionTable table;
    for (size_t i = 0; i < applicants_pointers.size(); ++i) {
        bool entered = false;
        for (size_t j = 0; j < (*(applicants_pointers[i])).wish_list.size(); j++) {
            for (size_t k = 0; k < universities_copy.size(); ++k) {
                if (universities_copy[k].name == (*(applicants_pointers[i])).wish_list[j] &&
                    universities_copy[k].max_students > 0) {
                    universities_copy[k].max_students--;
                    table[(*(applicants_pointers[i])).wish_list[j]].push_back(&(applicants_pointers[i]->student));
                    entered = true;
                    break;
                }
            }
            if (entered) {
                break;
            }
        }
    }
    return table;
}
