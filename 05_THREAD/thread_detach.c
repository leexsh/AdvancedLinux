void * thread_job(void * arg)
{
		pthread_t mtid = *(pthread_t *)arg;
		pthread_detach(pthread_self()); //将自己设置成分离态
		while(1)
		{
				printf("thread tuning......\n");
				sleep(1);
		}
}


int main(void)
{
		int err;
		pthread_t tid;
		pthread_t mtid;
		mtid = pthread_self();
		pthread_create(&tid,NULL,thread_job,(void*)&mtid);
		sleep(1);
		if((err = pthread_join(tid,NULL))>0)
		{
				printf("pthread join error:%s\n",strerror(err));
				exit(0);
		}
		return 0;
}
