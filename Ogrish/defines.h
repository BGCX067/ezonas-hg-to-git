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

#define SGLT_APP Application :: getSingletonPtr()
#define SGLT_CAM Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW Application :: getSingletonPtr() -> GetRW()
#define SGLT_LOG LogManager::getSingleton().getDefaultLog()
#define OG_SGLT Ogre::Singleton

#define PRINTLOG(s) LogManager::getSingleton().getDefaultLog()->logMessage(s)
