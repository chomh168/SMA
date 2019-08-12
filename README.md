SMTP - 경고 발생시 이메일 전송

사용라이브러리
MIME라이브러리 사용

파라미터
받는 주소, 제목, 내용

메일을 보내는 경우
-경보 발생 및 해제
-수집프로그램 다운 및 재가동

================================

COMMON - 인증 및 에러코드

hstec_sms

api_key = 'NCSAQFXDV4A9MSBR'
api_secret = 'KW2EBGUWUFZ1TLUMZ0XFS8DBDFLDMPT8'
sender_phone = '01025383553'

sms - 송신 번호, 발전소 번호, 메시지 내용 설정

sendSms - 문자 발송


authority.py - 인증관련

expireTime : 인증 만료 시간 (40분)

Key를 만들고 Key를 10분 단위로 체크

================================

DB - 데이터 베이스 연결

mongodb 

접속 주소 - mongodb://59.24.103.23:20100/solar

MongoClient을 이용하여 접속

database 확인 - database(collector)

statics로 접근도 가능 - databases[collector]

mysql

접속 주소 - mysql://stpm:stpm1234@121.159.30.15:3306/solar

parse_uri, connect 실행하여 접속

statics로 접근도 가능

================================

FRAMEWORK - 

context - 

===================================

SERVER

*repositories - db에 쿼리 및 삽입, 삭제

#hstec_solar

-init : 기본적인 변환 함수 정의

-hstec_solar_repository : HstecSolarRepository 클래스 안에 접근자 정의 

-table_customer : mysql db로부터 customer 테이블 데이터를 가져옴

-table_daygeneration : mysql db로부터 daygeneration 테이블 데이터를 가져옴 & 데이터를 삽입함

-table_daytotalgeneration : mysql db로부터 daytotalgeneration 테이블 데이터를 가져옴 & 데이터를 삽입함(하나 혹은 대량)

-table_inverter : mysql db로부터 inveter 테이블 데이터를 가져옴

-table_inveterlog : mysql db로부터 daytotalgeneration 테이블 데이터를 가져옴 & 데이터를 삽입함(하나 혹은 대량)

-table_smslog : mysql db로부터 smslog 테이블 데이터를 입력

-table_timegeneration : mysql db로부터 timegeneration 테이블 데이터를 입력


#mongo_solar

-init : 연결 및 컬렉션 생성 

GetDataInDistributedCollection : 여러 컬랙션에 걸쳐서 쿼리
MakeCollectionNameAtTimeRange : 시간기간을 컬랙션을 만듬
MakeCollectionNameAtDateAt : 일기간 컬랙션을 만듬

-collection_client_status :  정전 현황 컬랙션 데이터를 가져옴

-collection_command_queue : 명령 queue 삽입 삭제 참조

-collection_conn_box_log : 접속반 로그 검색

-collection_conn_box : 접속반 검색

-collection_customer : 고객정보 테이블 참조

-collection_day_generation : 일일발전량 기간을 이용해서 참조

-collection_day_total_generation : 누적발전량 기간을 이용해서 참조

-collection_event_log : 기간을 통해 이벤트 로그 검색

-collection_event_type : 이벤트 타입을 분류(mail or sms)

-collection_event : 이벤트를 가져오거나 넣거나 이벤트에 대한 알림을 설정

-collection_inveter : 인버터 정보를 가져옴, 

GetInverter(query) : 단일
GetInverterV2(mcnos) : 여러개

-collection_inverterlog : 인버터 로그 데이터를 가져옴

GetInverterLog(query) : 단일 로그 검색
GetInverterLogV2(mcno,dateAtFrom,dateAtTo) : 기간별 로그 검색
GetInverterLogV3(mcnos,dateAtFrom,dateAtTo) : 기간별 여러 발전소 검색

-collection_key_value : key(_id) 값을 통한 검색

-collection_login_history : 로그인 기록 검색, 생성, 삭제, 갱신

-collection_power_station : 발전소 검색

-collection_remote_ip : remote ip 검색

-collection_SensorName : Sensorname 검색

-collection_Sms_log : SMS 발송 내역 검색

-collection_StaticsInverterAvg : 인버터 평균값을 검색

-collection_StaticsInverterMedian : 인버터 메디안 검색

-collection_temprature : 온도 검색

-collection_time_generation : 인버터 시간별 발전량 검색

-collection_users : 고객정보를 검색

GetUsers(query) : 쿼리문을 통해 검색
GetUsersV2(userid,name,mcno) : 유저아이디 혹은 이름 혹은 발전소 번호를 통해 검색

-mongo_solar_repository : 저장소에 접근할 수 있는 접근자 함수


*ClientStatusAdapter

-client_status_adapter : collection_client_status 로부터 데이터를 가져옴(단일 혹은 맵)

GetClientStatus : 단일 데이터 반환
GetClientStatusMap : 맵 데이터 반환

-command_adapter : collection_command_queue 로부터 명령 커맨드를 검색, 삽입, 삭제

-conn_box_adapter : collection_conn_box_log 로부터 현재 접속반 데이터와 로그 검색

GetConnBox : 현재 데이터 값
GetConnBoxLog : 데이터 로그값

-customer_adapter : hstec_solar_repository 와 mongo_solar_repository 로부터 고객정보를 가져옴

GetCustomer : Mysql DB 로부터 정보를 가져옴
GetCustomerMongo : MongoDB 로부터 정보를 가져옴

-event_adapter : collection_event_type 와 collection_event 로부터 이벤트를 가져옴

-eventlog_adapter : collection_event_log로 부터 로그를 검색 및 이벤트 입려

-generation_adapter : 생성값들을 검색

GetDayGeneration : mysql db 검색
GetDayGenerations : mongo db 검색
GetDayGenerationV1 : mongo db 특정날 데이터 검색
GetDayTotalgeneration : 특정기간동안 전체 누적값 검색
GetDayTotalgenerationV1 : 특정날 전체 누적값 검색
GetDayTotalgenerationWithDateAtArr : 특정날까지 전체 누적값 검색
GetTimegenerations : 시간별 발전량 검색

-inverter_adapter : 인버터에 관련된 데이터 검색

GetInverterLog : Mysql DB 로부터 로그 검색
GetInverter : Mysql DB 로부터 인버터 정보 검색
GetInverterV2 : Mongo DB 로부터 인버터 정보 검색
GetInverterV3 : Mongo DB 로부터 특정 날의 정보 검색
GetInverterV4 : Mongo DB 로부터 여러 인버터 검색
GetInverterLogV2 : Mongo DB 로부터 로그 검색 
GetInverterLogV3 : MongoDB로부터 특정 기간동안 로그 검색
GetInverterLogV4 : MongoDB로부터 여러 발전소 특정 기간동안 로그 검색
GetStaticsInverterAvg : 인버터 평균 발전량 조회
GetStaticsInverterMedian : 인버터 메디안 조회
GetStaticsInverterAvgV1 : 특정날 평균 발전량 조회

-key_value_adapter : 키값을 통해 mongodb 검색

-login_history_adapter : mongo db로부터 로그인 기록 조회, 삽입, 갱신, 삭제

-power_stations_adapter : 발전소 정보를 검색

GetPowerStations : mongo db로부터 단일 발전소 정보를 검색
GetPowerSattionsV1 : mongo db로부터 발전소 번호를 통해 검색
GetPowerSattionsV2 : mongo db로부터 발전소 번호를 통해 검색
GetNotAvaliableMcnos : 발전소 현재 상황 검색

-remote_ip_adapter : remoteip 검색

-sms_log_adapter : SMS log 입력(mysql,mongodb)

-temprature_adapter : 온도 정보 검색

-user_adapter : 유저 정보 검색

GetUsers : 쿼리문을 통해 검색
GetUsersV2 : 유저아이디, 이름, 발전소번호를 통해 검색



*handler

#authority

-authority_get : 로그인 영역 만약 로그인시 아이디를 찾을 수 없을시 로그인이 안되고 로그인시 로그인 기록

-login_get : 로그인 조건(userid와 passwd 모두 일치시 로그인 아닐시 안되는 이유 반환)

-logout_get : 로그아웃 loginhistory를 없애고 로그아웃 메시지를 반환함

-reauthority_get : loginHistroy를 통해 로그인 중일때 로그인을 허락하지 않는 규칙 정의 


#command

-command_delete : 명령어를 삭제함

-command_get : mcno와 invno을 통해 명령어를 가지고 옴

-command_post : 명령어를 전송함

-migration_d1_get : migration_schedule_day1 shell 명령어를 통해 마이그레이션


#customer

-v1.customer_get : CustomerGetV1Handler class는 mysql db로부터 사용자 정보를 가져온다

-v2.customer_get : CustomerGetV2Handler class는 mongo db로부터 사용자 정보를 가져온다

#event

-v1.event_get : 입력 파라미터를 mcnos, all, userChecked, reutrnFormat을 변경시켜 이벤트를 반환한다

-v1.event_type_get : type을 받아들여 어댑터를 이용하여 반환받은 값을 반환해준다.

-v1.event_type_put : eventtype을 정해서 어댑터에 넣어준다.

#evnet_log

-v1.event_get : 특정 기간동안 특정 발전소의 이벤트 로그를 반환해준다

-v1.event_log_get : 이벤트 데이터를 가공하여 반환함

-v1.event_notify_get : 특정기간동안 100~299 타입을 가진 이벤트를 반환한다

-v1.event_notify_put : events를 받아아서 userCheck를 true후 반환한다

#generation_adapter

-v1.day_generation_get : mcno과 invno을 통해 mysql DB로부터 데이터를 가져온후 반환한다

-v2.day_generation_get : mcno과 invno을 통해 mongo DB로부터 데이터를 가져온후 반환한다

-v2.day_generation_sum_get : 발전소별 일발전량의 합산을 반환한다.

-v2.generation_realtime_local_get : 지역별 평균 발전량을 구한다.

-v2.generation_run_time_get : 발전소 가동시간 계산

-v2.generation_summary_get : 요약 페이지에 정보를 표시하기 위한 현재값, 월발전량, 년발전량 계산

-v2.month_generation_get : 월발전량을 계산, 인버터별 반환

-v2.month_generation_sum_get : 월발전량 계산, 모든 인버터의 합산

-v2.time_generation_get : 시간별 발전량 계산, 인버터별 반환

-v2.time_generation_sum_get : 시간별 발전량 계산, 모든 인버터 합산

#inverter

v1 mysql db로 부터 데이터를 가져옴

-v1.inverter_dckw_avg_get : 특정 발전소의 DCKW 값의 평균을 반환

-v1.inverter_dckw_get : 특정 발전소의 DCKW값 반환

-v1.inverter_dckw_sum_get : 특정 발전소의 DCKW값의 합산을 반환

-v1.inverter_get : 특정 발전소의 데이터를 반환

-v1.inverter_log_latest_get : 가장 최근 로그 검색

-v1.inverter_realtime_get : 인버터의 실시간 값을 반환

-v1.inverter_status_realtime : dckw 와 daytotal와 함께 데이터 반환

-v1.inverter_time_get : 특정 시간대 인버터 로그 반환

v2 mongo db로부터 데이터를 가져옴

-v2.inverter_avg_get : mongo db로부터 인버터의 평균값 반환

-v2.inverter_dckw_avg_get : mongo db로부터 특정날 평균 ACKW 반환

-v2.inverter_dckw_get : mongodb로부터 특정기간 동안 ACKW 값 반환

-v2.inverter_dckw_median_get : mongdb로부터 특정날 메디안 ACKW 반환

-v2.inverter_dckw_sum_get : mongodb로부터 특정기간 동안 ACKW 합 반환

-v2.inverter_get : mongodb내 inverter 데이터를 날짜를 반환

-v2.inverter_realtime_get : 인버터를 나누어 데이터를 저장후 반환

-v2.inverter_status_realtime : 현재 ACKW와 daytotal 값을 반환

v3 실시간 에러체크

-v3.inverter_realtime : 에러체크 및 피크값 체크

101 발전시작
102 발전정지
201 정전
202 통신에러
203 미발전


#keyvalue

-v1.keyvalue : 키에 대한 값을 반환, 없을시 400이라는 코드를 반환

-v1.keyvalue_put : key값에 대한 value를 갱신


#monitoring

-v1.monitoring_comm_get : 발전중인지의 여부와 통신에러 여부를 반환

-v1.monitoring_error_get : 에러에 대한 분류 작업

-v1.monitoring_get : 발전소 페이지를 위한 데이터 반환

-v1.monitoring_mini_get : 단순히 인버터만을 반환

-v1.monitoring_overview_get : 간략히 보기 페이지를 위한 데이터 반환 


#power_station

-v1.power_stations_get : 어댑터로부터 발전소 정보를 반환

-v1.power_station_list_get : 사용자 아이디로 부터 발전소 목록에 데이터와 함께 반환

-v2.power_stations_get : mongo db로부터 받은 정보를 반환

#seach

-v1.autocomplete_list : 자동 완성이 되도록 데이터 목록을 반환

#status

-v1.status_get : 상태값에 대한 결과값을 변환

powerstationStatus : 정상 0, ACKW값이 0일시 1
commStatus : 통신에러시 0

-v2.status_get : 상태값에 대한 결과값을 반환

powerstationStatus : 정상 0, ACKW값이 0일시 1
commStatus : 통신에러시 0

#users

-v1.user_info_get : userid를 이용하여 발전소 정보를 반환하고 로그인 기록에 기록

-v1.users_get : 입력 파라미터(userid,authority,name,mangager,mcno,isConnected)를 이용하여 유저정보 획득

#framework 

-router : url 정의 및 경로 정의

===========================================

BATCH

#mysql

-upload_day_generation_mysql : mongo db로 부터 데이터를 받아 mysql db에 daykw값을 기록

-upload_day_total_generation_mysql : mongo db로 부터 데이터를 받아 mysql db에 totkw값을 기록

-upload_invereterlog_mysql : mongo db로 부터 데이터를 받아 mysql db에 inverterlog값을 기록


-save_new_inverter : 입력 받은 데이터를 바탕으로 mongodb에 인버터 정보를 생성

-update_client_status : 입력 받은 client_status 데이터를 갱신

-update_command_history : 입력 받은 command_history 데이터를 갱신

-update_conn_box : 입력 받은 conn_box 데이터를 갱신

-update_connboxvoltage : 입력 받은 connboxvoltage 데이터를 갱신

-update_customer : 입력 받은 customer 데이터를 갱신

-update_day_generation : 입력 받은 day_generation 데이터를 갱신, 없다면 삽입, 전체 일일발전량 합산 갱신

-update_day_total_generation : 입력 받은 day_total_generation 데이터를 갱신, 없다면 삽입, 전체 일일발전량 합산 갱신

-update_invereter_log : 입력 받은 inverterlog 데이터를 갱신

-update_inverter : 입력 받은 inverter 정보를 mysql db에 migration

-update_inverter2 : 입력 받은 inverter 정보를 mongodb에 갱신

-update_inverterlog_fail : 인버터 로그 실패 기록

-update_key_value : 입력 받은 key_value 데이터 갱신

-update_login_history : 입력받은 login_history 데이터 갱신

-update_power_stations : 입력받은 powerstations 데이터 갱신

-update_remoteip : 입력받은 remoteip 데이터 갱신

-update_run_alert : 입력받은 runalert 데이터 갱신

-update_sensor_name : 입력받은 sensor_name 데이터 갱신

-update_sensor_type : 입력받은 sensor_type 데이터 갱신

-update_server_status : 입력받은 server_status(서버가동여부) 데이터 갱신

-update_temperature : 입력받은 temperature 데이터를 mysql db에 migration

-update_time_generation : 입력받은 time_generation 데이터를 갱신

-update_zipaddress : mysql db로부터 받은 zipaddress 데이터 migration

-upload_conn_box_log : mysql db로부터 받은 conn_box_log 데이터 migration

-upload_daygeneration : mysql db로부터 받은 daygeneration 데이터 migration

-upload_daytotalgeneration : mysql db로부터 받은 daytotalgeneration 데이터 migration

-upload_event_log : mysql db로부터 받은 event_log 데이터 migration

-upload_event : mysql db로부터 받은 event 데이터 migration

-upload_inverterlog : mysql db로부터 받은 inverterlog 데이터 migration

-upload_inverterlog2 : mysql db로부터 받은 inverterlog2 데이터 migration, 데이터가 없을시 0으로 초기화된 로그 생성

-upload_mysql_time_generation : mysql db로부터 받은 time_generation 데이터 migration

-upload_sms_log : mysql db로부터 받은 sms_log 데이터 migration

-upload_statistic_inverter_avg : statistics.inverter_avg 로부터 받은 평균값을 mongodb에 저장

-upload_statistic_inverter_median : statistics.inverter_median 로부터 받은 median값을 mongodb에 저장

-upload_timegeneration : mysql db로부터 받은 timegeneration 데이터 migration




#propergator

-alerter_collect : 수집된 데이터 발전소의 상태를 이메일 혹은 문자를 보냄

-alerter_heartbeat : 수집 서버에 대한 상태를 메일 혹은 문자로 보냄


#processor

-check_authorty_expire : login_history로부터 시간을 받아 비교후 만료를 결정

-process_inverter_avg : 로그로부터 합과 평균을 계산하여 context 형태로 반환

-process_inverter_log : 일일발전량을 12시에 리셋, inverter doc으로부터 inverterlog를 만듦

-process_inverter_median : inverterlog로부터 median값을 계산하여 median문서에 저장

-process_time_generation : 시간별 발전량 계산, 현재시간으로 부터 1시간을 뺀시간으로부터 발전량 계산

조건1 : 0시일시 timekw 값은 0
조건2 : timekw값이 0보다 작을시 0

*reliability 

-check_target_mcno : 발전소 상태중 사용안함과 진행중 이외의 상태 발전소를 반환

-check_update_inverter : 인버터 에러 상태체크

상태1 : 발전   - 이상상태에서 발전변경시 알림, isRun 상태 변경
상태2 : 발전중지 - 이상상태에서 발전변경시 알림(ACKW기준), isRun 상태 변경
상태3 : 정전   - 상태값을 확인후 알림
상태4 : 통신에러 - 60분간 미수집시 알림
상태5 : 가동정지 - 20분 이상 발전중지시 알림

-heartbeat : 수집프로그램이 정상 가동체크 및 내용 반환


*migration : mysql db로부터 받은 데이터를 migration에 저장


#controller

-check_command_complete : reset 명령후 지정된 휴대번호로 리셋 완료 메시지를 보냄

HstecSms.sendSms(010xxxxyyyy,message) 등록

-inverterlog : 로그 수집 절차, 절차중 에러발생시 step과 error 메시지를 통해 반환

SolarInverterCollector->SolarInverterLogCollector->InverterLogProcessor->
InverterLogStorer->DayGenerationStorer->DayTotalGenerationStorer->MysqlInverterLogStorer

-mysql_total_generation : mysql total generation만 따로 저장하는 절차

SolarInverterCollector->SolarInverterLogCollector->InverterLogProcessor->
MysqlDayGenerationStorer->MysqlDayTotalGenerationStorer

-time_generation : 시간별 발전량을 저장하는 절차

SolarInverterCollector->SolarInverterLogCollector->SolarTimeGenerationCollector
->TimeGenerationProcessor->TimeGenerationStorer->MysqlTimeGenerationStorer

*statistics

-upload_inverter_avg : 특정기간동안의 평균값을 계산

-upload_inverter_median : 특정기간동안의 메디안값을 계산

*reliability 

-dup_inverter : 중복검사

-heartbeat : 수집프로그램 검사

SolarServerStatusCollector->SolarHeartbeatCollector->SolarAdminCollector->
HeartbeatProcessor->ServerStatusStorer->AlertHeartbeat

-reliability_collect_inverter : 문제가 발생한 발전소들을 Map에 저장하여 함수를 통해 반환

KeyValueCollector.collect(context) - 검색하기 위한 key, 쿼리를 누적
MakeMcnoMap : 문제가 생간 발전소 모음

*migration

-migration_* : mysql db로부터 migration을 거쳐 mongo db에 데이터를 저장

-schedule.migaration_day_1 : 하루마다 할 작업 정의 

migration_client_status
migration_remoteip
migration_user
migration_sensor_name
migration_sensor_type
migration_temperature
migartion_zippaddress

-schedule.migaration_daygeneretion_d01 : 하루마다 일일발전량 누적발전량 실행

migration_daygeneration
migration_daytotalgeneration

-schedule.migration_inverter_m10 : 10분마다 인버터와 인버터로그 실행

migration_inverter
migration_inverterlog

-schedule.migration_minute_10 : 10분마다 할 작업정의

migration_event_log
migration_smslog
migration_conn_box
migration_connboxvoltage
migration_conboxlog


#collector

*hstec_solar_mongodb : mongodb에 쿼리를 위한 함수 정의

*hstec_solar_mysql : mysqldb에 쿼리를 위한 함수 및 스키마 정의















