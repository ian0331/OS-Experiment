package jobScheduling;

public class TimeConverter {

    public static int convertTimeToMinutes(String time) {
        String[] parts = time.split(":");
        if (parts.length != 2) {
            throw new IllegalArgumentException("时间格式不正确");
        }

        int hours = Integer.parseInt(parts[0]);
        int minutes = Integer.parseInt(parts[1]);

        return hours * 60 + minutes;
    }

    public static String convertMinutesToTime(int totalMinutes) {
        int hours = totalMinutes / 60;
        int minutes = totalMinutes % 60;

        return String.format("%02d:%02d", hours, minutes);
    }
}