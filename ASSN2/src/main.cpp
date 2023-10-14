#include <iostream>

#include "aggregator/avg_aggregator.hpp"
#include "aggregator/max_aggregator.hpp"
#include "aggregator/min_aggregator.hpp"
#include "student.hpp"
#include "student_database.hpp"
#include "util.hpp"

using namespace std;

/**
 * Student Database
 *
 * Database for students data.
 * Provides menu for user to add, delete, print list, and pivot table.
 */
int main() {
  StudentDatabase stu_db{};
  bool exit(false);

  // loop until exit
  while (!exit) {
    try {
      cout << "---------MENU----------" << endl;
      cout << "1. Add a student" << endl;
      cout << "2. Delete a student" << endl;
      cout << "3. Print the student's list" << endl;
      cout << "4. Pivot Table" << endl;
      cout << "5. Exit" << endl;
      cout << "-----------------------" << endl;

      const int option = util::get_menu_input(1, 5);
      switch (option) {
        case 1: {
          /** Add a student */
          const Student stu = util::get_student_info();
          stu_db.save_node(stu);
          cout << "A student is added in table!" << endl;
          break;
        }
        case 2: {
          /** Delete a student */
          const Student stu = util::get_student_info();
          stu_db.delete_node(stu);
          cout << "Deleted!" << endl;
          break;
        }
        case 3: {
          /** Print the student's list */
          stu_db.print_list();
          break;
        }
        case 4: {
          /** Pivot Table */
          cout << "-------Category--------" << endl;
          cout << "1. Dept" << endl;
          cout << "2. Gender" << endl;
          cout << "3. Dept and Gender" << endl;
          cout << "-----------------------" << endl;
          const int pivot_option = util::get_menu_input(1, 3);
          PivotColumn pivot_column;
          if (pivot_option == 1) {
            pivot_column = PivotColumn::Dept;
          } else if (pivot_option == 2) {
            pivot_column = PivotColumn::Gender;
          } else if (pivot_option == 3) {
            pivot_column = PivotColumn::DeptGender;
          } else {
            throw string("Assertion failed, invalid pivot option");
          }

          cout << "-------Function--------" << endl;
          cout << "1. Average" << endl;
          cout << "2. Max" << endl;
          cout << "3. Min" << endl;
          cout << "-----------------------" << endl;
          const int agg_option = util::get_menu_input(1, 3);

          // configure aggregator for pivot table operation
          Aggregator* agg = nullptr;
          if (agg_option == 1) {
            agg = new AvgAggregator{};
          } else if (agg_option == 2) {
            agg = new MaxAggregator{};
          } else if (agg_option == 3) {
            agg = new MinAggregator{};
          } else {
            throw string("Assertion failed, invalid selection for aggregator");
          }

          // execute pivot
          stu_db.pivot_table(pivot_column, *agg);
          delete agg;
          break;
        }
        case 5: {
          /** Exit */
          exit = true;
          break;
        }
      }
    } catch (const string& err) {
      // If an exception is thrown, print the error message and continue
      cout << err << endl;
    }
  }
}