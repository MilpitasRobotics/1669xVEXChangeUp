#include "main.h"
#include "okapi/api.hpp"
using namespace okapi;
using namespace okapi::literals;
std::shared_ptr<okapi::OdomChassisController> test = ChassisControllerBuilder()
	.withMotors({4, 3}, {2, 5}) // pass motors to odomchassiscontroller builder
	.withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0058, 0.00057, 0.00025 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 })  // Angle controller gains
		.withDimensions(AbstractMotor::GearsetRatioPair(AbstractMotor::gearset::blue, 7.0/3.0), {{4.125_in, 12.75_in}, imev5BlueTPR})
		.withOdometry() // use the same scales as the chassis (above)
		.withMaxVelocity(200)
		.buildOdometry();
auto myChassis =
  okapi::ChassisControllerBuilder()
    .withMotors({4,3}, {2, 5})
		.withDimensions(AbstractMotor::GearsetRatioPair(AbstractMotor::gearset::blue, 7.0/3.0), {{4.125_in, 12.75_in}, imev5BlueTPR})
    .build();

		auto test2 =
		  AsyncMotionProfileControllerBuilder()
		    .withLimits({
		      0.8,  //max velocity
		      2.0,  //max acceleration
		      10.0  //max jerk
		    })
		    .withOutput(myChassis)
		    .buildMotionProfileController();
void autonhandler(int auton){
  if(auton == 0){
		setintake(-600);
		pros::delay(200);
		setintake(0);
		test2->generatePath({
			{0_in,0_in,0_deg},
			{36_in,0_in,0_deg}},
			"A"
		);
		test2->setTarget("A");
		test2->waitUntilSettled();
		test->turnToAngle(-70_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{24_in,0_in,0_deg}},
			"B"
		);
		setintake(600);
		indexer.move_velocity(600);
		test2->setTarget("B");
		test2->waitUntilSettled();
		pros::delay(500);
		setintake(0);
		launcher.move_velocity(600);
		pros::delay(500);
		launcher.move_velocity(-600);
		indexer.move_velocity(-600);
		setintake(-600);
		test->moveDistance(-14_in);
		test2->waitUntilSettled();
		launcher.move_velocity(0);
		indexer.move_velocity(0);
		setintake(0);
		test->turnAngle(-145_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{48_in,0_in,0_deg}},
			"C"
		);
		test2->setTarget("C");
		test2->waitUntilSettled();
		test->turnAngle(95_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{16_in,0_in,0_deg}},
			"D"
		);
		/*test2->setTarget("D");
		test2->waitUntilSettled();
		setintake(600);
		indexer.move_velocity(600);
		launcher.move_velocity(600);
		pros::delay(500);
		setintake(0);
		pros::delay(200);
		launcher.move_velocity(0);
		indexer.move_velocity(0);*/
	}
	if(auton==1){
		setintake(-600);
		pros::delay(100);
		setintake(600);
		test2->generatePath({
			{0_in,0_in,0_deg},
			{24_in,0_in,0_deg}},
			"A"
		);
		test2->setTarget("A");
		test2->waitUntilSettled();
		test->turnAngle(-143_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{28_in,0_in,0_deg}},
			"B"
		);
		test2->setTarget("B");
		test2->waitUntilSettled();
		indexer.move_velocity(600);
		launcher.move_velocity(600);
		pros::delay(800);
		setintake(0);
		pros::delay(400);
		indexer.move_velocity(-600);
		launcher.move_velocity(-600);
		setintake(-600);
		pros::delay(200);
		test->moveDistance(-24_in);
		test->waitUntilSettled();
		setintake(0);
		launcher.move_velocity(0);
		indexer.move_velocity(0);
	}
	if(auton == 2){
		setintake(-600);
		pros::delay(200);
		setintake(0);
		test2->generatePath({
			{0_in,0_in,0_deg},
			{36_in,0_in,0_deg}},
			"A"
		);
		test2->setTarget("A");
		test2->waitUntilSettled();
		test->turnToAngle(60_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{24_in,0_in,0_deg}},
			"B"
		);
		setintake(600);
		indexer.move_velocity(600);
		test2->setTarget("B");
		test2->waitUntilSettled();
		pros::delay(500);
		setintake(0);
		launcher.move_velocity(600);
		pros::delay(500);
		launcher.move_velocity(-600);
		indexer.move_velocity(-600);
		setintake(-600);
		test->moveDistance(-14_in);
		test2->waitUntilSettled();
		launcher.move_velocity(0);
		indexer.move_velocity(0);
		setintake(0);
		test->turnAngle(143_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{48_in,0_in,0_deg}},
			"C"
		);
		test2->setTarget("C");
		test2->waitUntilSettled();
		test->turnAngle(-95_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{16_in,0_in,0_deg}},
			"D"
		);
		test2->setTarget("D");
		test2->waitUntilSettled();
		setintake(600);
		indexer.move_velocity(600);
		launcher.move_velocity(600);
		pros::delay(500);
		setintake(0);
		pros::delay(300);
		launcher.move_velocity(0);
		indexer.move_velocity(0);
	}
	if(auton==3){
		setintake(-600);
		pros::delay(100);
		setintake(600);
		test2->generatePath({
			{0_in,0_in,0_deg},
			{24_in,0_in,0_deg}},
			"A"
		);
		test2->setTarget("A");
		test2->waitUntilSettled();
		test->turnAngle(140_deg);
		test->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{30_in,0_in,0_deg}},
			"B"
		);
		test2->setTarget("B");
		test2->waitUntilSettled();
		indexer.move_velocity(600);
		launcher.move_velocity(600);
		pros::delay(800);
		setintake(0);
		pros::delay(400);
		indexer.move_velocity(-600);
		launcher.move_velocity(-600);
		setintake(-600);
		pros::delay(200);
		test->moveDistance(-24_in);
		test->waitUntilSettled();
		setintake(0);
		launcher.move_velocity(0);
		indexer.move_velocity(0);
	}
	if(auton==4){
		setintake(-600);
		pros::delay(200);
		setintake(600);
		test2->generatePath({
			{0_in,0_in,0_deg},
			{10_in,0_in,-45_deg}},
			"A"
		);
		test2->setTarget("A");
		test2->waitUntilSettled();
		test2->generatePath({
			{0_in,0_in,0_deg},
			{8_in,0_in,0_deg}},
			"B"
		);
		//test2->setTarget("B");
		test2->waitUntilSettled();
		indexer.move_velocity(600);
		launcher.move_velocity(600);
		pros::delay(800);
		setintake(0);
		pros::delay(400);
		indexer.move_velocity(-600);
		launcher.move_velocity(-600);
		setintake(-600);
		pros::delay(200);
	}





		//setintake(-600);
		//pros::delay(300);
		//setintake(0);
		//pros::delay(500);
		//test->moveDistance(34_in);
		//test->waitUntilSettled();
		//test->turnAngle(-70_deg);
		//test->waitUntilSettled();
		//setintake(600);
		//indexer.move_velocity(600);
		//test->moveDistance(20_in);
		//pros::delay(200);
		//test->stop();
		//pros::delay(500);
		//launcher.move_velocity(600);
		//pros::delay(1000);
		//indexer.move_velocity(0);
		//launcher.move_velocity(0);
		//setintake(0);
	}
