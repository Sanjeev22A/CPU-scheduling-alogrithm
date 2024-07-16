import matplotlib.pyplot as plt

# Read average waiting time, turnaround time, and average response time from RR and IRR files
def read_data(filename):
    with open(filename, "r") as file:
        lines = file.readlines()
        avg_waiting_time = float(lines[0].split()[3])
        avg_turnaround_time = float(lines[1].split()[3])
        avg_response_time = float(lines[2].split()[3])
    return avg_waiting_time, avg_turnaround_time, avg_response_time

avg_waiting_time_rr, avg_turnaround_time_rr, avg_response_time_rr = read_data("waiting_turnaround_response_time_rr.txt")
avg_waiting_time_irr, avg_turnaround_time_irr, avg_response_time_irr = read_data("waiting_turnaround_response_time_irr.txt")

# Plotting the comparison graph
labels = ['Round Robin (RR)', 'Improved Round Robin (IRR)']
avg_waiting_times = [avg_waiting_time_rr, avg_waiting_time_irr]
avg_turnaround_times = [avg_turnaround_time_rr, avg_turnaround_time_irr]
avg_response_times = [avg_response_time_rr, avg_response_time_irr]

x = range(len(labels))

plt.figure(figsize=(10, 6))

plt.subplot(1, 3, 1)
plt.bar(x, avg_waiting_times, color=['blue', 'orange'])
plt.xlabel('Algorithm')
plt.ylabel('Average Waiting Time')
plt.title('Comparison of Average Waiting Time')
plt.xticks(x, labels)

plt.subplot(1, 3, 2)
plt.bar(x, avg_turnaround_times, color=['blue', 'orange'])
plt.xlabel('Algorithm')
plt.ylabel('Average Turnaround Time')
plt.title('Comparison of Average Turnaround Time')
plt.xticks(x, labels)

plt.subplot(1, 3, 3)
plt.bar(x, avg_response_times, color=['blue', 'orange'])
plt.xlabel('Algorithm')
plt.ylabel('Average Response Time')
plt.title('Comparison of Average Response Time')
plt.xticks(x, labels)

plt.tight_layout()
plt.show()
