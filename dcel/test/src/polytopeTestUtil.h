
#ifndef POLYTOPETESTUTIL_H_
#define POLYTOPETESTUTIL_H_

#include "polytope.h"


namespace chtest
{
	bool equivalentOp( ch::half_edge he1, ch::half_edge he2 );

	void addFaceTo( ch::polytope& polyt, ch::vid_t v1, ch::vid_t v2, ch::vid_t v3, bool expVal = false );
	void removeFaceFrom( ch::polytope& polyt, ch::fid_t f, bool expVal = true );

	void checkFacesIn( const ch::polytope& polyt, const std::vector<ch::fid_t>& faceIds );
	void checkHalfEdgesIn( const ch::polytope& polyt, ch::fid_t fid, const std::vector<ch::heid_t>& heIds );
	void checkHalfEdgesIn( const ch::polytope& polyt, ch::fid_t fid, const std::vector<ch::vid_t >&  vIds );
	void checkVerticesIn( const ch::polytope& polyt, ch::fid_t f, ch::vid_t v1, ch::vid_t v2, ch::vid_t v3 );
	void checkHalfEdgesAroundVertex(const ch::polytope& polyt, ch::vid_t vid,
									const std::vector<ch::heid_t>& expHalfEdges );

	void checkNonExistingFacesIn( const ch::polytope& polyt, const std::vector<ch::fid_t>& faceIds );

	void mergeFaces( ch::polytope& polyt, ch::fid_t fid1, ch::fid_t fid2, bool expVal = true );
	void checkMergedFace( ch::polytope& polyt, const std::vector<ch::vid_t>& vertIds, bool first = false );
}

#endif /* POLYTOPETESTUTIL_H_ */
