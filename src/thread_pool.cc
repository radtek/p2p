#include "thread_pool.h"

thread_pool::thread_pool(
	const int & thread_limit_in
):
	thread_limit(new int(thread_limit_in)),
	stop_threads(new bool(false)),
	threads(new int(0))
{

}

thread_pool::~thread_pool()
{

}

void thread_pool::join()
{
	while(**threads){
		portable_sleep::yield();
	}
}

void thread_pool::process()
{
	++**threads;
	boost::function0<void> func;
	while(true){
		if(**stop_threads){
			break;
		}

		{//begin lock scope
		boost::mutex::scoped_lock lock(Mutex);
		if(work_queue.empty()){
			//no jobs, terminate thread
			break;
		}
		func = work_queue.front();
		work_queue.pop();
		}//end lock scope

		func();
	}
	--**threads;
}

void thread_pool::queue(const boost::function0<void> & func)
{
	boost::mutex::scoped_lock lock(Mutex);

	if(**stop_threads){
		return;
	}

	work_queue.push(func);
	if(**threads < **thread_limit){
		boost::thread Thread(boost::bind(&thread_pool::process, this));
	}
}

void thread_pool::terminate()
{
	**stop_threads = true;
	join();
}
