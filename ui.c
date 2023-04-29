{
        // Create new student node
        StudentNode *newAcademicProbationNode = malloc(sizeof(StudentNode));
        newAcademicProbationNode->pStudent = student;
        newAcademicProbationNode->pNext = NULL;

        // Insert student into Honor Roll list in order of GPA
        StudentNode *prev = NULL;
        StudentNode *curr = db->pAcademicProbationList;
        while (curr != NULL && student->gpa > curr->pStudent->gpa)
        {
            prev = curr;
            curr = curr->pNext;
        }
        if (prev == NULL)
        {
            newAcademicProbationNode->pNext = db->pAcademicProbationList;
            db->pAcademicProbationList = newAcademicProbationNode;
        }
        else
        {
            prev->pNext = newAcademicProbationNode;
            newAcademicProbationNode->pNext = curr;
        }
    }