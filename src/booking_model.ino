import 'package:cloud_firestore/cloud_firestore.dart';

class Booking {
  final DateTime date;
  final String time;
  final String pulley;


  Booking({
    required this.date,
    required this.time,
    required this.pulley,
  });

  factory Booking.fromSnapshot(DocumentSnapshot snapshot) {
    Map<String, dynamic> data = snapshot.data() as Map<String, dynamic>;

    DateTime date = (data['date'] as Timestamp).toDate();
    String time = data['time'] is int ? data['time'].toString() : data['time'];
    String pulley =
        data['pulley'] is int ? data['pulley'].toString() : data['pulley'];

    return Booking(
      date: date,
      time: time,
      pulley: pulley,
    );
  }
}
