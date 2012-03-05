#define BULLET_MAX 8

#define REINIT(node) { node -> setPosition(0,0,0); node->setOrientation(Quaternion()); }


#define ITV(T)    std::vector	<T>::Iterator	
#define ITA(T)    std::array	<T>::Iterator	
#define ITQ(T)    std::queue	<T>::Iterator	
#define ITD(T)    std::deque	<T>::Iterator	
#define ITL(T)    std::list		<T>::Iterator	
#define ITM(T,U)  std::map		<T,U>::Iterator 
#define ITS(T)    std::stack	<T>::Iterator	

#define TO_STR StringConverter :: toString
#define FOR(I) for(size_t i = 0; i < I; ++i)
#define FOR_VECT(vect, type) for(std::vector<type>::iterator it = vect.begin(); it != vect.end(); ++it)
#define FOR_VECT2(vect, type) for(std::vector<type>::iterator it2 = vect.begin(); it2 != vect.end(); ++it2)

#define ITER_VECT(type) std::vector<type>::iterator

#define SGLT_LOG LogManager::getSingleton().getDefaultLog()
#define PRINTLOG(s) LogManager::getSingleton().getDefaultLog()->logMessage(s)
