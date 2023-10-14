assn2/
|-- src/
|   |-- aggregator/
|   |   |-- avg_aggregator.cpp
|   |   |-- max_aggregator.cpp
|   |   `-- min_aggregator.cpp
|   |
|   |-- util/
|   |   |-- get_menu_input.cpp
|   |   |-- get_student_info.cpp
|   |   `-- is_upper.cpp
|   |
|   |-- main.cpp
|   `-- student_database.cpp
| 
`-- include/
    |-- aggregator/
    |   |-- avg_aggregator.h
    |   |-- max_aggregator.h
    |   `-- min_aggregator.h
    |
    |-- aggregator.hpp
    |-- dept.hpp
    |-- list.hpp
    |-- student_database.hpp
    |-- student.hpp
    `-- util.hpp

src/ : 소스파일
main.cpp : 프로그램 진입점 정의, 사용자로부터 입력을 받아 StudentDatabase 클래스의 메서드를 호출
student_database.cpp : 학생 데이터를 linked list로 관리하여, 학생 정보를 추가, 삭제, 출력, pivot 연산을 수행하는 클래스 정의
util/get_menu_input.cpp : 사용자의 메뉴 입력을 받아 검증하고 예외처리 및 입력값을 반환하는 함수 정의
util/get_student_info.cpp : 사용자에게서 학생 정보 입력을 받아 검증하고 예외처리 후 Student 객체를 생성하여 반환하는 함수 정의
util/is_upper.cpp : 문자열을 받아 대문자인지 검증하고, 대문자이면 true, 아니면 false를 반환하는 함수 정의
aggregator/avg_aggregator.cpp : age를 누적하여 입력받고, 학생 수로 나누어 평균을 구하는 클래스 정의
aggregator/max_aggregator.cpp : age를 누적하여 입력받고, 최대값을 구하는 클래스 정의
aggregator/min_aggregator.cpp : age를 누적하여 입력받고, 최소값을 구하는 클래스 정의


include/ : 헤더파일
util.hpp : 유틸리티 함수 선언. get_menu_input.cpp, get_student_info.cpp, is_upper.cpp의 헤더파일
aggregator/avg_aggregator.h : avg_aggregator.cpp의 헤더파일
aggregator/max_aggregator.h : max_aggregator.cpp의 헤더파일
aggregator/min_aggregator.h : min_aggregator.cpp의 헤더파일
aggregator.hpp : avg/max/min aggregator의 base class인 Aggregator를 정의
dept.hpp : 학과를 나타내는 데이터 타입 정의 (멤버: 학과 이름, 학생 수)
student.hpp : 학생 정보를 나타내는 데이터 타입 정의 (멤버: 학과, 성별, 이름, 나이)
list.hpp : linked list를 구현한 클래스 정의
student_database.hpp : student_database.cpp의 헤더파일

**변경 내용**
1. 리스트는 템플릿으로 구현되어 있음. 
  - int dept_cnt, string dept[9]가 사라짐. 대신, StudentDatabase 클래스를 정의하여 멤버로 Student의 리스트와 Dept의 리스트를 관리하도록 하였음.
2. Student 클래스의 메서드 void input_info()는 삭제되었고, 대신 util/get_student_info.cpp에 정의된 함수를 사용하도록 함. (보고서 참조)
3. sort() 함수는 매개변수로 string metric 대신 비교 함수의 함수 포인터를 받음. (보고서 참조)

**추가 내용**
1. list의 head를 노출하지 않기 위한 방법으로, range-based for loop을 사용하기 위해 Iterator와 begin() 및 end() 메서드를 정의하였음.
2. 학과 정보를 다루기 위한 Dept 클래스를 정의하였음.
3. StudentDatabase 클래스를 정의하여 필요한 부분만 public method로 노출하도록 캡슐화 하였음.
4. 유틸리티 함수의 선언은 util.hpp에, 정의는 각각의 소스파일에 작성하였음.