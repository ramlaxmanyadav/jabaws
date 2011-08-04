package compbio.runner.sequence;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;

import org.apache.log4j.Logger;

import compbio.data.sequence.ScoreManager;
import compbio.data.sequence.SequenceUtil;
import compbio.data.sequence.UnknownFileFormatException;
import compbio.engine.client.SkeletalExecutable;
import compbio.metadata.ResultNotAvailableException;

public class AAProperties extends SkeletalExecutable<AAProperties>{
	private static Logger log = Logger.getLogger(AAProperties.class);
	
	public AAProperties(){
		addParameters(Arrays.asList("-jar"));
	}

	@SuppressWarnings("unchecked")
	@Override
	public ScoreManager getResults(String workDirectory)
			throws ResultNotAvailableException {
		ScoreManager sequences = null;
		try {
			InputStream inStream = new FileInputStream(new File(workDirectory,
					getOutput()));
			sequences = ScoreManager.newInstanceSingleScore(SequenceUtil
					.readJRonn(inStream));
			inStream.close();
		} catch (FileNotFoundException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		} catch (IOException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		} catch (UnknownFileFormatException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		} catch (NullPointerException e) {
			log.error(e.getMessage(), e.getCause());
			throw new ResultNotAvailableException(e);
		}
		return sequences;
	}

	@SuppressWarnings("unchecked")
	@Override
	public Class<AAProperties> getType() {
		return (Class<AAProperties>) this.getClass();
	}

}
