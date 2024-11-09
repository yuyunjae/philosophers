<h1> Dining philosophers problem </h1>
<br> 식사하는 철학자 문제에 대한 코드입니다.
<br><h2>clone 및 compile 방법 </h2>
git clone [repository address] [directory name]
<br> cd [directory name]/philo
<br> make
<br><h2> 실행 방법 </h2>
1.
<br> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
<br> 2.
<br> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
<h2></h2>
◦ number_of_philosophers : The number of philosophers and also the number of forks.
<br>
◦ time_to_die : If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
<br>
◦ time_to_eat : The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
<br>
◦ time_to_sleep : The time a philosopher will spend sleeping.
<br>
◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. 
<br>If not specified, the simulation stops when a philosopher dies.
<br><br>[time_to_die], [time_to_eat], [time_to_sleep], [number_of_times_each_philosopher_must_eat] are in milliseconds.
<br><br> [number_of_philosophers] <= 200 (recommand)
<br> [time_to_die], [time_to_eat], [time_to_sleep], [number_of_times_each_philosopher_must_eat] >= 60 (recommand)
