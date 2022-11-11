# 운영체제에 설치된 cmake의 최소 요구 버전
cmake_minimum_required(VERSION 3.0.2)

# 패키지의 이름으로, package.xml에서 입력한 패키지 이름을 그대로 사용
project(test_pkg)

# 캐킨 빌드할 시 요구되는 구성 요소 패키지. 사용자가 만든 패키지가 의존하는 다른 패키지를 먼저 설치하는 옵션
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roscpy
  std_msgs
)

# ROS 이외의 패키지를 사용하는 예: Boost를 사용할 때 system 패키지를 설치하도록 함
find_package(Boost REQUIRED COMPONENTS system)


# 파이썬을 이용하기 위해 rospy를 사용할 때 설정하는 옵션. 파이썬 설치 프로세스인 setup.py를 부르는 역할
catkin_python_setup()


# 메시지 파일을 추가
# FILES: 현재 패키지 폴더의 msg 폴더 안의 .msg 파일들을 참조해 헤더 파일(.h)를 자동으로 생성한다는 의미
# 만약 새 메시지를 만든다면 msg 폴더를 만든 뒤 그 안에 있는 메시지 파일 이름을 입력함. 여기에서는 MyMessage1.msg 등이 그 예.

add_message_files(
   FILES
   Message1.msg
   Message2.msg
   )

# 사용하는 서비스 파일을 추가. 방식은 메시지 파일과 같으며, 사용하려면 srv 폴더를 만든 뒤 해당 파일 이름을 입력해둬야 한다.
 add_service_files(
   FILES
   Service1.srv
   Service2.srv
 )

# 사용하는 서비스 파일을 추가. 방식은 메시지, 서비스 파일과 같다.
 add_action_files(
   FILES
   Action1.action
   Action2.action
 )

# 의존하는 메시지를 설정
# DEPENDENCIES: 아래에 해당하는 메시지 패키지를 사용한다는 의미
# std_msgs, sensor_msgs가 그 예시
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

# 캐킨 빌드 옵션
## INCLUDE: 뒤에 설정한 패키지 내부 폴더인 include의 헤더 파일을 사용함
## LIBRARIES: 뒤에 설정한 패키지의 라이브러리를 사용함
## CATKIN_DEPENDS: 의존하는 패키지 지정
## DEPENDS: 시스템 의존 패키지
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES test_pkg
#  CATKIN_DEPENDS roscpp roscpy std_msgs
#  DEPENDS system_lib
)

# include 폴더 지정
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  # 사용자가 추가할 때는 이 밑의 공간 이용
)


# 빌드 후 생성할 라이브러리. C++을 사용할 경우!
 add_library(${PROJECT_NAME}
   src/${PROJECT_NAME}/test_pkg.cpp
 )

# 해당 라이브러리 및 실행파일을 빌드하기 전, 생성해야 할 의존성이 있는 메시지와 dynamic reconfigure이 있다면 우선으로 수행하도록 함
 add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# 빌드 후 생성할 실행파일에 대한 옵션 지정
## `__실행 파일 이름__` `__참조할 파일__` 순서대로 기재
## 복수 개의 참조 .cpp 파일이 있을 경우 한 괄호 뒤에 연속적으로 기재
## 생성할 실행파일이 2개 이상일 경우 add_executable 항목을 추가함
 add_executable(${PROJECT_NAME}_node src/test_pkg_node.cpp)

# 지정 실행 파일을 생성하기 전, 링크해야 하는 라이브러리와 실행파일을 링크함
 target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
 )
