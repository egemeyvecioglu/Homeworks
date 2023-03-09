import java.util.ArrayList;

public class PlaylistTree {

	public PlaylistNode primaryRoot;		//root of the primary B+ tree
	public PlaylistNode secondaryRoot;	//root of the secondary B+ tree
	public PlaylistTree(Integer order) {
		PlaylistNode.order = order;
		primaryRoot = new PlaylistNodePrimaryLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new PlaylistNodeSecondaryLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addSong(CengSong song) {
		// TODO: Implement this method
		// add methods to fill both primary and secondary tree
		// Find the leaf node where the new record should be inserted
		addSongToPrimary(song);
		addSongToSecondary(song);

	}
	public void addSongToPrimary(CengSong song)
	{
		PlaylistNode curr = primaryRoot;
		while (curr instanceof  PlaylistNodePrimaryIndex) {
			PlaylistNodePrimaryIndex internalNode = (PlaylistNodePrimaryIndex) curr;
			int n = internalNode.audioIdCount();
			for (int i = 0; i < n; i++) {
				if (song.audioId() < internalNode.audioIdAtIndex(i)) {
					curr = internalNode.getChildrenAt(i);
					break;
				}
				else
				{
					curr = internalNode.getChildrenAt(i+1);
				}
			}

		}

		PlaylistNodePrimaryLeaf leaf = (PlaylistNodePrimaryLeaf) curr;
		int n = leaf.songCount();
		int added=0;
		int i;

		for(i = 0; i < n; i++)
		{
			if(song.audioId() < leaf.audioIdAtIndex(i))
			{
				leaf.addSong(i, song);
				added =1;
				break;
			}
		}if(added==0)leaf.addSong(i,song);



		if (leaf.songCount() > PlaylistNode.order*2) {
			PlaylistNodePrimaryLeaf newLeftLeaf = new PlaylistNodePrimaryLeaf(leaf.getParent());
			PlaylistNodePrimaryLeaf newRightLeaf = new PlaylistNodePrimaryLeaf(leaf.getParent());
			newLeftLeaf.level =newRightLeaf.level =leaf.level;
			int k = leaf.songCount()/2;
			for(int i1 = 0; i1<k;i1++)
			{
				newLeftLeaf.addSong(i1,leaf.songAtIndex(i1));
			}
			for(int i1 = k;i1<leaf.songCount();i1++)
			{
				newRightLeaf.addSong(i1-k,leaf.songAtIndex(i1));
			}

			if (leaf == primaryRoot) {
				ArrayList<Integer> audioIds = new ArrayList<Integer>();
				audioIds.add(leaf.audioIdAtIndex(k));
				ArrayList<PlaylistNode> children = new ArrayList<PlaylistNode>();
				children.add(newLeftLeaf);
				children.add(newRightLeaf);
				PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null,audioIds,children);
				newRoot.level = leaf.level+1;
				primaryRoot = newRoot;
				newRightLeaf.setParent(newRoot);
				newLeftLeaf.setParent(newRoot);

			}
			else {
				PlaylistNodePrimaryIndex parent =(PlaylistNodePrimaryIndex) leaf.getParent();

				int ind = leaf.audioIdAtIndex(k);
				int g =0;
				added = 0;
				for(; g<(parent.audioIdCount());g++) {
					if(ind<parent.audioIdAtIndex(g)) {
						parent.addAudioId(g, ind);
						added = 1;
						System.out.println(g);
						break;
					}
				}if(added==0)parent.addAudioId(g,ind);
				int egem = parent.removeChildren(leaf);
				parent.addChildrenatIndex(egem,newLeftLeaf);
				parent.addChildrenatIndex(egem+1,newRightLeaf);
				newRightLeaf.setParent(parent);
				newLeftLeaf.setParent(parent);

				// If the parent is now overfull, split it and repeat the process
				while (parent.audioIdCount() > PlaylistNode.order*2) {
					PlaylistNodePrimaryIndex newLeftInternal = new PlaylistNodePrimaryIndex(parent.getParent());
					PlaylistNodePrimaryIndex newRightInternal = new PlaylistNodePrimaryIndex(parent.getParent());
					newLeftInternal.level =newRightInternal.level =parent.level;
					int j = parent.audioIdCount()/2;
					for(int i1 = 0; i1<=j;i1++)
					{
						if(i1!=j)newLeftInternal.addAudioId(i1,parent.audioIdAtIndex(i1));
						newLeftInternal.addChildren(parent.getChildrenAt(i1));
						(parent.getChildrenAt(i1)).setParent(newLeftInternal);
					}
					for(int i1 = j+1;i1<= parent.audioIdCount();i1++)
					{
						if(i1!=leaf.songCount())newRightInternal.addAudioId(i1-j-1,parent.audioIdAtIndex(i1));
						newRightInternal.addChildren(parent.getChildrenAt(i1));
						(parent.getChildrenAt(i1)).setParent(newRightInternal);
					}

					if (parent == primaryRoot) {
						ArrayList<Integer> audioIds1 = new ArrayList<Integer>();
						audioIds1.add(parent.audioIdAtIndex(k));
						ArrayList<PlaylistNode> children1 = new ArrayList<PlaylistNode>();
						children1.add(newLeftInternal);
						children1.add(newRightInternal);
						PlaylistNodePrimaryIndex newRoot = new PlaylistNodePrimaryIndex(null,audioIds1,children1);
						newRoot.level = parent.level+1;
						primaryRoot = newRoot;
						newRightInternal.setParent(newRoot);
						newLeftInternal.setParent(newRoot);
						break;
					}
					PlaylistNodePrimaryIndex temp = parent;
					parent = (PlaylistNodePrimaryIndex) parent.getParent();
					int ind2 = parent.removeChildren(temp);
					parent.addAudioId(ind2,temp.audioIdAtIndex(j));
					parent.addChildrenatIndex(ind2,newLeftInternal);
					parent.addChildrenatIndex(ind2+1,newRightInternal);
				}
			}
		}
		return;
	}

	public void addSongToSecondary(CengSong song)
	{
		PlaylistNode curr = secondaryRoot;
		while (curr instanceof  PlaylistNodeSecondaryIndex) {
			PlaylistNodeSecondaryIndex internalNode = (PlaylistNodeSecondaryIndex) curr;
			int n = internalNode.genreCount();
			for (int i = 0; i < n; i++) {
				if (song.genre().compareTo(internalNode.genreAtIndex(i)) < 0) {
					curr = internalNode.getChildrenAt(i);
					break;
				}
				else
				{
					curr = internalNode.getChildrenAt(i+1);
				}
			}

		}

		PlaylistNodeSecondaryLeaf leaf = (PlaylistNodeSecondaryLeaf) curr;
		int n = leaf.genreCount();
		int added=0;
		int i;
		int exists = 0;
		for(i = 0; i < n; i++)
		{//System.out.println("for içi: "+song.genre()+"  "+leaf.genreAtIndex(i));
			if(song.genre().compareTo(leaf.genreAtIndex(i)) <= 0)
			{
				System.out.println(song.audioId()+ " added.");
				leaf.addSong(i, song);
				added =1;
				break;
			}

		}
		//System.out.println("dış if önce: "+song.genre()+"  "+leaf.genreAtIndex(i)+  "    " + added);
		//System.out.println((song.genre().equals(leaf.genreAtIndex(i))));
		if(added==0 && exists==0) {
			leaf.addSong(i, song);
			System.out.println(song.audioId()+ " addedwfs.");
		}


		if (leaf.genreCount() > PlaylistNode.order*2) {
			PlaylistNodeSecondaryLeaf newLeftLeaf = new PlaylistNodeSecondaryLeaf(leaf.getParent());
			PlaylistNodeSecondaryLeaf newRightLeaf = new PlaylistNodeSecondaryLeaf(leaf.getParent());
			newLeftLeaf.level =newRightLeaf.level =leaf.level;
			int k = leaf.genreCount()/2;
			ArrayList<ArrayList<CengSong>> songBucket = leaf.getSongBucket();
			for(int i1 = 0; i1<k;i1++)
			{
				ArrayList<CengSong> songs = songBucket.get(i1);
				for(int i2 = 0; i2<songs.size();i2++) {
					newLeftLeaf.addSong(i1, songs.get(i2));
				}
			}

			for(int i1 = k;i1<leaf.genreCount();i1++)
			{
				ArrayList<CengSong> songs = songBucket.get(i1);
				for(int i2 = 0; i2<songs.size();i2++) {
					newRightLeaf.addSong(i1 - k, songs.get(i2));
				}
			}

			if (leaf == secondaryRoot) {
				ArrayList<String> genres = new ArrayList<String>();
				genres.add(leaf.genreAtIndex(k));
				ArrayList<PlaylistNode> children = new ArrayList<PlaylistNode>();
				children.add(newLeftLeaf);
				children.add(newRightLeaf);
				PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null,genres,children);
				newRoot.level = leaf.level+1;
				secondaryRoot = newRoot;
				newRightLeaf.setParent(newRoot);
				newLeftLeaf.setParent(newRoot);

			}
			else {
				PlaylistNodeSecondaryIndex parent =(PlaylistNodeSecondaryIndex) leaf.getParent();

				String new_genre = leaf.genreAtIndex(k);
				int g =0;
				added = 0;
				for(; g<(parent.genreCount());g++) {
					if(new_genre.compareTo(parent.genreAtIndex(g))<0) {
						parent.addGenre(g, new_genre);
						added = 1;
						System.out.println(g);
						break;
					}
				}if(added==0)parent.addGenre(g,new_genre);
				int egem = parent.removeChildren(leaf);
				parent.addChildrenatIndex(egem,newLeftLeaf);
				parent.addChildrenatIndex(egem+1,newRightLeaf);
				newRightLeaf.setParent(parent);
				newLeftLeaf.setParent(parent);

				// If the parent is now overfull, split it and repeat the process
				while (parent.genreCount() > PlaylistNode.order*2) {
					PlaylistNodeSecondaryIndex newLeftInternal = new PlaylistNodeSecondaryIndex(parent.getParent());
					PlaylistNodeSecondaryIndex newRightInternal = new PlaylistNodeSecondaryIndex(parent.getParent());
					newLeftInternal.level =newRightInternal.level =parent.level;
					int j = parent.genreCount()/2;
					for(int i1 = 0; i1<=j;i1++)
					{
						if(i1!=j)newLeftInternal.addGenre(i1,parent.genreAtIndex(i1));
						newLeftInternal.addChildren(parent.getChildrenAt(i1));
						(parent.getChildrenAt(i1)).setParent(newLeftInternal);
					}
					for(int i1 = j+1;i1<= parent.genreCount();i1++)
					{
						if(i1!=leaf.genreCount())newRightInternal.addGenre(i1-j-1,parent.genreAtIndex(i1));
						newRightInternal.addChildren(parent.getChildrenAt(i1));
						(parent.getChildrenAt(i1)).setParent(newRightInternal);
					}

					if (parent == secondaryRoot) {
						ArrayList<String> genres1 = new ArrayList<String>();
						genres1.add(parent.genreAtIndex(k));
						ArrayList<PlaylistNode> children1 = new ArrayList<PlaylistNode>();
						children1.add(newLeftInternal);
						children1.add(newRightInternal);
						PlaylistNodeSecondaryIndex newRoot = new PlaylistNodeSecondaryIndex(null,genres1,children1);
						newRoot.level = parent.level+1;
						secondaryRoot = newRoot;
						newRightInternal.setParent(newRoot);
						newLeftInternal.setParent(newRoot);
						break;
					}

					PlaylistNodeSecondaryIndex temp = parent;
					parent = (PlaylistNodeSecondaryIndex)  parent.getParent();
					int ind2 = parent.removeChildren(temp);
					parent.addGenre(ind2,temp.genreAtIndex(j));
					parent.addChildrenatIndex(ind2,newLeftInternal);
					parent.addChildrenatIndex(ind2+1,newRightInternal);

				}
			}
		}
		return;
	}
	public CengSong searchSong(Integer audioId) {
		// TODO: Implement this method
		// find the song with the searched audioId in primary B+ tree
		// return value will not be tested, just print according to the specifications
		PlaylistNode temp = primaryRoot;
		int tab_counter = 0;
		while(temp != null)
		{

			if(temp instanceof PlaylistNodePrimaryLeaf)
			{

				PlaylistNodePrimaryLeaf leafNode = (PlaylistNodePrimaryLeaf) temp;
				int n = (leafNode).songCount();

				for(int i = 0 ; i < n; i++)
				{
					CengSong song = (leafNode).songAtIndex(i);

					if(song != null && song.audioId()==audioId)
					{
						for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
						System.out.println("<data>");
						for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
						System.out.println("<record>"+song.audioId()+"|"+song.genre()+"|"+song.songName()+"|"+song.artist()+"</record>");
						for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
						System.out.println("</data>");
						return song;
					}
				}
				System.out.println("Could not find " + audioId);
				return null;
			}

			else if(temp instanceof  PlaylistNodePrimaryIndex)
			{
				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println("<index>");
				PlaylistNodePrimaryIndex internalNode = (PlaylistNodePrimaryIndex) temp;
				int n = (internalNode).audioIdCount();
				int stop = 0;
				for(int i = 0 ; i < n; i++)
				{
					for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
					System.out.println(internalNode.audioIdAtIndex(i));
					if (audioId < internalNode.audioIdAtIndex(i)) {
						if(stop==0)temp = internalNode.getChildrenAt(i);
						stop = 1;
					}
					else
					{
						if(stop==0)temp = internalNode.getChildrenAt(i+1);
					}
				}
				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println("</index>");
				tab_counter++;
			}
		}
		return  null;
	}


	public void printPrimaryPlaylist() {
		// TODO: Implement this method
		// print the primary B+ tree in Depth-first order
		PlaylistNode node = primaryRoot;
		int tab_counter=0;
		myPrintprimaryList(node,tab_counter);

	}

	public void myPrintprimaryList(PlaylistNode node, int tab_counter)
	{
		if(node instanceof PlaylistNodePrimaryLeaf)
		{
			PlaylistNodePrimaryLeaf leafNode = (PlaylistNodePrimaryLeaf) node;
			int n = (leafNode).songCount();
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("<data>");
			for(int i = 0 ; i < n; i++)
			{
				CengSong song = (leafNode).songAtIndex(i);

				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println("<record>"+song.audioId()+"|"+song.genre()+"|"+song.songName()+"|"+song.artist()+"</record>");
			}
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("</data>");

			return;
		}

		else if(node instanceof  PlaylistNodePrimaryIndex)
		{
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("<index>");
			PlaylistNodePrimaryIndex internalNode = (PlaylistNodePrimaryIndex) node;
			int n = (internalNode).audioIdCount();
			for(int i = 0 ; i < n; i++)
			{
				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println(internalNode.audioIdAtIndex(i));
			}
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("</index>");
			for(int i = 0 ; i <= n; i++)myPrintprimaryList(internalNode.getChildrenAt(i),tab_counter+1);


			tab_counter++;
		}

		return;
	}

	public void printSecondaryPlaylist() {
		// TODO: Implement this method
		// print the secondary B+ tree in Depth-first order
		PlaylistNode node = secondaryRoot;
		int tab_counter=0;
		myPrintSecondaryList(node,tab_counter);
		return;
	}

	public void myPrintSecondaryList(PlaylistNode node, int tab_counter)
	{
		if(node instanceof PlaylistNodeSecondaryLeaf)
		{
			PlaylistNodeSecondaryLeaf leafNode = (PlaylistNodeSecondaryLeaf) node;
			int n = (leafNode).genreCount();
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("<data>");
			for(int i = 0 ; i < n; i++)
			{
				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println(leafNode.genreAtIndex(i));
				ArrayList<CengSong> songs = leafNode.songsAtIndex(i);
				for(int i1=0;i1<songs.size();i1++)
				{
					CengSong song = songs.get(i1);

					for(int tb =0;tb<tab_counter+1;tb++)System.out.print("\t");
					System.out.println("<record>"+song.audioId()+"|"+song.genre()+"|"+song.songName()+"|"+song.artist()+"</record>");
				}
			}
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("</data>");

			return;
		}

		else if(node instanceof  PlaylistNodeSecondaryIndex)
		{
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("<index>");
			PlaylistNodeSecondaryIndex internalNode = (PlaylistNodeSecondaryIndex) node;
			int n = (internalNode).genreCount();
			for(int i = 0 ; i < n; i++)
			{
				for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
				System.out.println(internalNode.genreAtIndex(i));
			}
			for(int tb =0;tb<tab_counter;tb++)System.out.print("\t");
			System.out.println("</index>");
			for(int i = 0 ; i < internalNode.getAllChildren().size(); i++)myPrintSecondaryList(internalNode.getChildrenAt(i),tab_counter+1);

		}

		return;
	}

	// Extra functions if needed

}


